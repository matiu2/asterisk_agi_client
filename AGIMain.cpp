#include "AGI.hpp"
#include <iostream>
#include <fstream>

int main(int, char**) {
    AGI::Protocol a(std::cin, std::cout);
    a.readConfig();
    const AGI::Config& config(a.config());
    std::fstream log("agi.log", std::ios_base::out);
    using std::endl;
    log << "agi_request: " << config.request << endl;
    log << "agi_channel: " << config.channel << endl;
    log << "agi_lang: " << config.language << endl;
    log << "agi_type: " << config.type << endl;
    log << "agi_callerid: " << config.callerid << endl;
    log << "agi_dnid: " << config.dnid << endl;
    log << "agi_context: " << config.context << endl;
    log << "agi_extension: " << config.extension << endl;
    log << "agi_priority: " << config.priority << endl;
    a.answer();
    log << "Channel status: " << a.channelStatus("fun channel");
}
