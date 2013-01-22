#include "proxy.hpp"
#include "errors.hpp"

#include <sstream>
#include <unordered_map>

namespace agi_proxy {

void Proxy::readConfig()
{
    log << "Reading Config..." << std::endl << std::flush;
    static std::unordered_map<std::string, std::string*>
    settings {
        {"agi_request", &_config.request},
        {"agi_channel", &_config.channel},
        {"agi_language", &_config.language},
        {"agi_type", &_config.type},
        {"agi_uniqueid", &_config.uniqueid},
        {"agi_version", &_config.version},
        {"agi_callerid", &_config.callerid},
        {"agi_calleridname", &_config.calleridname},
        {"agi_callingpres", &_config.callingpres},
        {"agi_callingani2", &_config.callingani2},
        {"agi_callington", &_config.callington},
        {"agi_callingtns", &_config.callingtns},
        {"agi_dnid", &_config.dnid},
        {"agi_rdnis", &_config.rdnis},
        {"agi_context", &_config.context},
        {"agi_extension", &_config.extension},
        {"agi_priority", &_config.priority},
        {"agi_enhanced", &_config.enhanced},
        {"agi_accountcode", &_config.accountcode},
        {"agi_threadid", &_config.threadid}
    };
    while (true) {
        // Read in a line
        std::string line1;
        std::getline(in, line1);
        // Break on a blank lene
        if (line1.empty())
            break;
        std::stringstream line(line1);
        // Read in the config item name
        std::string name;
        std::getline(line, name, ':');
        // Find which config storage operation to perform
        auto setting = settings.find(name);
        if (setting != settings.end()) {
            log << "Reading setting for '" << name << "'..." << std::flush;
            line >> *setting->second;
            log << "'" << *setting->second << "'" << std::endl << std::flush;
        } else {
            log << "Could not find setting for " << name << std::endl << std::flush;
            std::stringstream msg;
            msg << "No setting found for '"
                << name << "'";
            throw err::BadParse(msg.str());
        }
    }
}

int Proxy::getResult()
{
    /// Get's the code for a response and fast forwards the stream
    /// to the end of relult=
    // Multiline response looks like:
    // 200 result=0- name="x"
    // age=12
    // 200
    // Single line response is just
    // code result=0 [data]
    log << "getting result: ";
    Code code;
    in >> code >> std::ws;
    log << code << std::endl << std::flush;
    if (code != 200)
        throw err::BadCode(code);
    std::string resultLiteral;
    std::getline(in, resultLiteral, '=');
    if (resultLiteral != "result") {
        std::stringstream msg;
        msg << "Expected to find 'result' after code but got '"
            << resultLiteral << "' instead";
        throw err::BadParse(msg.str());
    }
    int result;
    in >> result;
    return result;
}

}
