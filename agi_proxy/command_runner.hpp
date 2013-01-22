#pragma once

#include <memory>
#include "commands/base.hpp"

namespace agi_proxy {

/// Experimental command runner class, handles memory management.
/// And can be stored in a vector to be run later
class CommandRunner {
public:
    CommandRunner(command::Base* command=nullptr) : _last_command(command) {}
    CommandRunner(CommandRunner&& other) : _last_command(std::move(other._last_command)) {}
    /// Just call like: myCommandRunner(new SomeCommand(proxy, arg1, arg2))
    command::Base* operator()(command::Base* command=nullptr) {
        if (command != nullptr)
            _last_command = std::unique_ptr<command::Base>(command);
        if (_last_command)
            (*_last_command)();
        return _last_command.get();
    }
    command::Base* lastCommand() {return _last_command.get();}
private:
    std::unique_ptr<command::Base> _last_command;
};

}
