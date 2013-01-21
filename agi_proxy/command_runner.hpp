#pragma once

#include <memory>
#include "command/base.hpp"

/// Experimental command runner class, handles memory management.
/// And can be stored in a vector to be run later
class CommandRunner {
public:
    CommandRunner(Command::Base* command=nullptr) : _last_command(command) {}
    /// Just call like: myCommandRunner(new SomeCommand(proxy, arg1, arg2))
    Command::Base* operator()(Command::Base* command) {
        _last_command = std::unique_ptr<Command::Base>(command);
        (*command)();
        return command;
    }
    Command::Base* lastCommand() {return _last_command.get();}
private:
    std::unique_ptr<Command::Base> _last_command;
};

