/// AGI Proxy class
#pragma once

#include <iostream>
#include <string>

#include "config.hpp"
#include "typedefs.hpp"

namespace agi_proxy {

namespace command {
    class Base;
}

class Proxy {
private:
    friend class command::Base;
    Config _config;
    std::istream& in;
    std::ostream& out;
    std::ostream& log;
public:
    Proxy(std::istream& aIn, std::ostream& aOut, std::ostream& aLog) : in(aIn), out(aOut), log(aLog) {}
    void readConfig();
    int getResult();
    const Config& config() { return _config; }
};

}
