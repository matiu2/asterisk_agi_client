/// The base for all AGI proxy commands

#pragma once
#include <istream>
#include <ostream>
#include <sstream>

#include "../proxy.hpp"
#include "../errors.hpp"

namespace agi_proxy {

namespace command {

class Base {
private:
    Proxy& _proxy;
    int _result = -1;
protected:
    std::istream& in = _proxy.in;
    std::ostream& out = _proxy.out;
    std::ostream& log = _proxy.log;
    int getResult() { return _result = proxy().getResult(); }
    virtual void checkResult() {
        int result = getResult();
        log << "Result: " << result << std::endl << std::flush;
        if (result != 0) {
            std::stringstream msg;
            msg << commandText() << " got non zero result: " << result;
            throw err::BadResult(msg.str());
        }
    }
    virtual const char* commandText() = 0;       /// Must be overriden and return the text that is to be sent by a command
    virtual void addParams(std::ostream&) {} /// Allows outputting of other parameters after the initial command text
public:
    Base(Proxy& proxy) : _proxy(proxy) {}
    virtual ~Base() {} // http://www.parashift.com/c++-faq/virtual-dtors.html
    Proxy& proxy() { return _proxy; }
    Base& operator ()() {
        // Log
        log << "Running command: " << commandText();
        addParams(log);
        log << std::endl << std::flush;
        // Do
        out << commandText();
        addParams(out);
        out << std::endl << std::flush;
        // Done
        checkResult();
        return *this;
    }
    int result() const { return _result; }
};

}
}
