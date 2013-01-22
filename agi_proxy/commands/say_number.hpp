/// Makes the agi server say a number
#pragma once

#include "base.hpp"

namespace agi_proxy {
namespace command {

class SayNumber: public Base {
public:
    SayNumber(Proxy& proxy, int number) :  Base(proxy), _number(number) {}
    int number() const { return _number; }
protected:
    virtual const char* commandText() { return "SAY NUMBER"; }
    virtual void addParams(std::ostream& out) { out << ' ' << _number; }
private:
    int _number;
};

}
}
