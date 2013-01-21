/// The base for all AGI proxy commands

#pragma once
#include <iostream>

namespace agi_proxy {

class AsteriskCallProxy;

namespace Command {

    class Base {
        /* this class shoud only have one function doing input output operation
        the fct: Execute will operate thru the AsteriskCallProxy on the asterisk server
        it should throw exceptions if anything fails
        */
    private:
        AsteriskCallProxy& _proxy;
        int _result = -1;
    protected:
        std::istream& in = _proxy.in;
        std::ostream& out = _proxy.out;
        std::ostream& log = _proxy.log;
        virtual void checkResult() {
            _result = proxy().getResult();
            log << "Result: " << result << std::endl << std::flush;
        }
        virtual const char* commandText() = 0;       /// Must be overriden and return the text that is to be sent by a command
        virtual void addParams(std::ostream& out) {} /// Allows outputting of other parameters after the initial command text
    public:
        Base(AsteriskCallProxy& proxy) : _proxy(proxy) {}
        virtual ~Base() {} // http://www.parashift.com/c++-faq/virtual-dtors.html
        AsteriskCallProxy& proxy() { return _proxy; }
        Base& operator ()() {
            // Log
            log << "Running command: " << commandText();
            addParams(log);
            log << std::endl << std::flush;
            // Do
            out << commandText();
            addParams(out);
            out << std::endl;
            // Done
            checkResult();
            return *this;
        }
        int result() const { return _result; }
    };

}
}
