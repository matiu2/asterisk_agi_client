#pragma once
#include <string>

namespace agi_proxy {

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

}
