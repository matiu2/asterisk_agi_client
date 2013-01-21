/// AGI Proxy class

#include <iostream>
#include <string>

#include "command/base.hpp"
#include "typedefs.hpp"

namespace agi_proxy {

namespace Command {
    class Base;
}

class Proxy {
private:
    std::istream& in;
    std::ostream& out;
    std::ostream& log;
    Config _config;
    friend class Command::Base;
public:
    Proxy(std::istream& aIn, std::ostream& aOut, std::ostream& aLog) : in(aIn), out(aOut), log(aLog) {}
    void readConfig();
    void answer();
    int getResult();
    ChannelStatus channelStatus(const std::string& channelName);
    ChannelStatus currentchannelStatus();
    int Getnumber3Digit(int timeout);
    int recordFile(std::string, std::string, int , int );
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
    /**
     * Asks asterisk to play a sound file.
     * @param filename the name of the file to play. Should be a file locally accessible to the Asterisk server.
     **/
    int StreamFile(const std::string& filename);
    /**
     * Makes Asterisk ask the phone user for a digit
     * @param timeout timeout in ms
     * @return the digit read from the phone user
     **/
    int GetDigit(int timeout );
    int SendText(string);
    int SendImage(string );
    int SayNumber(int);
    /*! \fnint SayNumber(int anyint);
    * \brief will ask asterisk to read a digit dtmf from usersk
    * \param anyint any int asterisk will read thousands... if need to read the number to user  .
    * \return  void if all ok.throws exception if failed to get the comand executed by asterisk
    */
    const Config& config() { return _config; }
    friend ostream& operator<< (ostream& stream, const Proxy& Proxy);
};

}
