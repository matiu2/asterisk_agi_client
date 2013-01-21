/// Makes the agi server say a number
#pragma once

#include "../errors.hpp"

namespace api_proxy {
namespace command {

class SayNumber: public Base {
public:
    SayNumber(AsteriskCallProxy& proxy, int number) :  Base(proxy), _number(number) {}
    virtual SayNumber& operator ()() {
        out << "SAY NUMBER " << _number << " \"\"\n"<<flush ;
        checkResult();
        return *this;
    }
    int number() const { return _number; }
protected:
    virtual void checkResult() {
        Base::checkResult();
        switch (result()) {
            case -1: throw err::BadResult("CONTROL STREAM FILE failed");
            case 0:  throw err::BadResult("CONTROL STREAM FILE failure on open");
        };
    }
    virtual const char* commandText() { return "SAY NUMBER"; }
    virtual void addParams(std::ostream& out) { out << ' ' << _number; }
private:
    int _number;
};

}
}
