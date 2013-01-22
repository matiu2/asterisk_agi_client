#include <string>
#include <sstream>
#include <stdexcept>

#include "typedefs.hpp"

namespace agi_proxy {

namespace err {

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
    std::string code2msg(Code aCode) {
        switch (aCode) {
            case 510: return "Invalid or unknown command";
            case 511: return "Command Not Permitted on a dead channel";
            case 520: return "End of proper usage";
        };
        std::stringstream msg("Unexpected Code: ");
        msg << aCode;
        return msg.str();
    }
    Code code;
    BadCode(Code aCode) : Error(code2msg(aCode)), code(aCode) {}
};

}
}
