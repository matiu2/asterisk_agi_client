#include "AGI.hpp"
#include <iostream>

int main(int, char**) {
    AGI::Protocol a(std::cin, std::cout);
    a.readConfig();
    const AGI::Config& config(a.config());
    using std::cerr;
    using std::endl;
    cerr << "agi_request: " << config.request << endl;
    cerr << "agi_channel: " << config.channel << endl;
    cerr << "agi_lang: " << config.language << endl;
    cerr << "agi_type: " << config.type << endl;
    cerr << "agi_callerid: " << config.callerid << endl;
    cerr << "agi_dnid: " << config.dnid << endl;
    cerr << "agi_context: " << config.context << endl;
    cerr << "agi_extension: " << config.extension << endl;
    cerr << "agi_priority: " << config.priority << endl;
    a.answer();
    std::cerr << "Channel status: " << a.channelStatus("fun channel");
}
