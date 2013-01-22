/// Makes asterisk answer the phone
#pragma once

#include "base.hpp"
#include <sstream>

namespace agi_proxy {
namespace command {

class ChannelStatus: public Base {
public:
    enum Status {
        downAvailable=0, // Channel is down and available
        downReserved=1,  // Channel is down, but reserved
        offHook=2,       // Channel is off hook
        dialling=3,      // Digits (or equivalent) have been dialed
        ringing=4,       // Line is ringing
        remoteRinging=5, // Remote end is ringing
        up=6,            // Line is up
        busy=7,          // Line is busy
        LAST=busy
    };
private:
    std::string _channelName;
public:
    ChannelStatus(Proxy& proxy, const std::string& channelName="") :  Base(proxy), _channelName(channelName) {}
    const std::string& channelName() const { return _channelName; }
    Status status() const { return (Status)result(); }
protected:
    virtual void checkResult() {
        int result = getResult();
        if ((result == -1) || (result > Status::LAST))  {
            std::stringstream msg;
            msg << "CHANNEL STATUS command needs a result betweeen 0 and "
                << Status::LAST << ", but got " << result << " instead";
            throw err::BadResult(msg.str());
        }
    }
    virtual const char* commandText() { return "CHANNEL STATUS"; }
    virtual void addParams(std::ostream& out) {
        if (!_channelName.empty())
            out << ' ' << _channelName;
    }
};

}
}

