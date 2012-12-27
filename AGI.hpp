#include <stdexcept>
#include <sstream>
#include <map>
#include <set>

namespace AGI {

typedef unsigned short Code;
typedef unsigned char Digit;

struct Error : std::logic_error {
    Error(const std::string& msg) : std::logic_error(msg) {}
};

struct BadParse : std::logic_error {
    BadParse(const std::string& msg) : std::logic_error(msg) {}
};

struct BadResult : std::logic_error {
    BadResult(const std::string& msg) : std::logic_error(msg) {}
};

struct BadCode : std::logic_error {
    static const std::map<Code, std::string> code2msg;
    std::string doCode2Msg(Code aCode) {
        auto found = code2msg.find(aCode);
        if (found == code2msg.end()) {
            std::stringstream msg("Unexpected Code: ");
            msg << aCode;
            return msg.str();
        } else {
            return found->second;
        }
    }
    Code code;
    BadCode(Code aCode) : std::logic_error(doCode2Msg(aCode)), code(aCode) {}
};

struct Config {
    std::string request;
    std::string channel;
    std::string language;
    std::string type;
    std::string uniqueid;
    std::string version;
    std::string callerid;
    std::string calleridname;
    std::string callingpres;
    std::string callingani2;
    std::string callington;
    std::string callingtns;
    std::string dnid;
    std::string rdnis;
    std::string context;
    std::string extension;
    std::string priority;
    std::string enhanced;
    std::string accountcode;
    std::string threadid;
    template <std::string& dest>
    void set(const std::string& value) { dest = value; }
};

class Protocol {
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
    std::istream& in;
    std::ostream& out;
    std::ostream& log;
    Config _config;
public:
    Protocol(std::istream& aIn, std::ostream& aOut, std::ostream& aLog) : in(aIn), out(aOut), log(aLog) {}
    int getResult();
    void readConfig();
    void answer();
    ChannelStatus channelStatus(const std::string& channelName);
    Digit controlStreamFile(
        const std::string& filename,
        const std::set<Digit>& digits={},
        int skipms=0,
        char ffchar='*',
        char rewchar='#',
        char pausechar=0
    );
    
    const Config& config() { return _config; }
    
};


}
