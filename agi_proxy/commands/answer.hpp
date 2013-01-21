/// Makes asterisk answer the phone
#pragma once

#include "../errors.hpp"
#include <sstream>

namespace api_proxy {
namespace command {

class Answer: public Base {
public:
    Answer(AsteriskCallProxy& proxy) :  Base(proxy), _number(number) {}
    virtual Anwser& operator ()() {
    int number() const { return _number; }
protected:
    virtual void checkResult() {
        Base::checkResult();
        if (result != 0) {
            std::stringstream msg;
            msg << "ANSWER command needs a result of 0, but got: " << result;
            throw BadResult(msg.str());
        }
    }
    virtual const char* commandText() { return "ANSWER"; }
};

}
}

