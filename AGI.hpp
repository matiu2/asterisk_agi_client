/** \file  AGI.hpp
*header file defining a Proxy class for agi type comunication with asterisk
*once runining in asterisk your prg can instantiate a Protocol object which will handle controling the asterisk server
*throwing exception if commands failed on the server
*\n
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:

 * =====================================================================================
 **/
#ifndef AGI_H
#define AGI_H
#include <stdexcept>
#include <sstream>
#include <map>
#include <set>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include "AGI.hpp"

using namespace std;
typedef unsigned short Code;
typedef unsigned char Digit;
struct Error : std::runtime_error {
    Error(const std::string& msg) : std::runtime_error(msg) {}
};
struct BadResult : Error {
    BadResult(const std::string& msg) : Error(msg) {}
};
struct BadParse : Error {
    BadParse(const std::string& msg) : Error(msg) {}
};


struct BadCode : Error {
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
    BadCode(Code aCode) : Error(doCode2Msg(aCode)), code(aCode) {}
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
};

namespace Command {
    class Base;
}

class AsteriskCallProxy {
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
    int _nbrcommandsent = 0,
        _nbrcommandok = 0,
        _nbrcommandfail =0;

    friend class Command::Base;
public:
    AsteriskCallProxy(std::istream& aIn, std::ostream& aOut, std::ostream& aLog) : in(aIn), out(aOut), log(aLog) {}
    void readConfig();
    void answer();
    int getResult();
    ChannelStatus channelStatus(const std::string& channelName);
    ChannelStatus currentchannelStatus();
    int Getnumber3Digit(int timeout);
    int recordFile(string, string, int , int );
    Digit controlSayNumber(int);
    int hangupcurrentchanel();
    int hangupchanel(const std::string& channelName);
    void databaseDel(const std::string& family, const std::string& key);


    Digit controlStreamFile(
        const std::string& filename,
        const std::set<Digit>& digits= {},
        int skipms=0,
        char ffchar='*',
        char rewchar='#',
        char pausechar=0
    );
    int StreamFile(string filename);
    /*! \fn void StreamFile(string filename)
    * \brief will ask asterisk to play the file.
    * \param filename a complete path of the file .
    * \return a void if all ok.throws exception if failed to get the comand executed by asterisk
    **/
    int GetDigit(int timeout );
    /*! \fn int GetDigit(int timeout );
    * \brief will ask asterisk to read a digit dtmf from user
    * \param timeout a timeout in ms .
    * \return the ascii code of input ok.throws exception if failed to get the comand executed by asterisk
    */
    int SendText(string);
    int SendImage(string );
    int SayNumber(int);
    /*! \fnint SayNumber(int anyint);
    * \brief will ask asterisk to read a digit dtmf from usersk
    * \param anyint any int asterisk will read thousands... if need to read the number to user  .
    * \return  void if all ok.throws exception if failed to get the comand executed by asterisk
    */



    const Config& config() {
        return _config;
    }
    int nbrcommandsent() {
        return _nbrcommandsent;
    }
    int nbrcommandok() {
        return _nbrcommandok;
    }
    int nbrcommandfail() {
        return _nbrcommandfail;
    }
    friend ostream& operator<< (ostream& stream, const AsteriskCallProxy& AsteriskCallProxy);
};

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
        virtual void checkResult();
    public:
        Base(AsteriskCallProxy& proxy) : _proxy(proxy) {}
        virtual ~Base() {} // http://www.parashift.com/c++-faq/virtual-dtors.html
        AsteriskCallProxy& proxy() { return _proxy; }
        virtual Base& operator ()() { return *this; }
        int result() const { return _result; }
        operator int() const { return result(); }
    };

    class SayNumber: public Base {
    public:
        SayNumber(AsteriskCallProxy& proxy, int number) :  Base(proxy), _number(number) {}
        virtual SayNumber& operator ()();
        int number() const { return _number; }
    protected:
        virtual void checkResult();
    private:
        int _number;
    };

} // namespace Command

#endif // AGI_H
