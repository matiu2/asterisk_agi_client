#include "agi_proxy/proxy.hpp"
#include "agi_proxy/command_runner.hpp"
#include "agi_proxy/commands/all.hpp"

#include <vector>
#include <fstream>
#include <iostream>

#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>

namespace bio = boost::iostreams;

int main(int, char**) {
    std::ofstream log;
    log.open ("info.log");

    // Logging
    bio::filtering_ostream live;
    live.push(bio::file_sink("live.log", std::ios_base::app));

    // std::out tee
    const bio::tee_filter<std::ostream> teeFilter(live);

    bio::filtering_ostream out;
    out.push(teeFilter);
    out.push(std::cout);
 
    // std::in tee
    bio::filtering_istream in;
    in.push(teeFilter, 0);
    in.push(std::cin, 0);

    // Make the proxy
    agi_proxy::Proxy p(in, out, log);
    p.readConfig();

    // Set up the commands
    namespace cmd = agi_proxy::command;
    agi_proxy::CommandRunner run;
    run(new cmd::Answer(p));
    run(new cmd::SayNumber(p, 42));
    run(new cmd::ChannelStatus(p));

    auto channel_status = dynamic_cast<cmd::ChannelStatus*>(run.lastCommand());

    switch (channel_status->status()) {
        case cmd::ChannelStatus::up: std::cout << "Channel is up: " << std::endl;
    };
    std::cout << "Channel Status is: " << channel_status->status() << std::endl;

}
