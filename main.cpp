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

    // Different ways of getting the channel status

    // 1. dynamic_cast
    run(new cmd::ChannelStatus(p));
    auto status1 = dynamic_cast<cmd::ChannelStatus*>(run.lastCommand());

    // 2. make your own pointer
    cmd::ChannelStatus* status2=nullptr;
    run(status2 = new cmd::ChannelStatus(p));

    // 3. just cast the result
    run(new cmd::ChannelStatus(p));
    auto status3 = (cmd::ChannelStatus::Status)run.lastCommand()->result();

    std::cout << "Status 1: " << status1->status() << std::endl;
    std::cout << "Status 2: " << status2->status() << std::endl;
    std::cout << "Status 3: " << status3 << std::endl;
}
