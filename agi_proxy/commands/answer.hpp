/// Makes asterisk answer the phone
#pragma once

#include "base.hpp"
#include <sstream>

namespace agi_proxy {
namespace command {

class Answer : public Base {
public:
    Answer(Proxy& proxy) : Base(proxy) {}
protected:
    virtual const char* commandText() { return "ANSWER"; }
};

}
}

