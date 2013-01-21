/// Makes asterisk answer the phone
#pragma once

#include "../errors.hpp"
#include <sstream>

namespace api_proxy {
namespace command {

class ChannelStatus: public Base {
public:
    enum ChannelStatus {
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
    ChannelStatus(AsteriskCallProxy& proxy, const std::string& channelName="") :  Base(proxy), _channelName(channelName) {}
    const std::string& channelName() const { return _channelName; }
    ChannelStatus status() const { return _channelName; }
protected:
    virtual void checkResult() {
        Base::checkResult();
        if ((result == -1) || (result > ChannelStatus::LAST))  {
            std::stringstream msg;
            msg << "CHANNEL STATUS command needs a result betweeen 0 and "
                << ChannelStatus::LAST << ", but got " << result << " instead";
            throw BadResult(msg.str());
        }
    }
    virtual const char* commandText() { return "CHANNEL STATUS"; }
    virtual void addParams(std::ostream& out) { out << ' ' << _number; }
};

}
}

