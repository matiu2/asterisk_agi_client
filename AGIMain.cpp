#include "AGI.hpp"
#include <iostream>
#include <fstream>

int main(int, char**)
{
     try {
          fstream log("agi.log", std::ios_base::out | std::ios_base::app);
          Protocol a(std::cin, std::cout, log);
          a.readConfig();

          log<<a;
          a.answer();
          log<<" \n controlStreamFile\n"<<flush;


          log<<" \n now: say number 1111\n"<<flush;
          a.controlSayNumber(111);
          log<< "Channel status: " << a.currentchannelStatus()<<endl<<flush;
          log<<" \nnow:  say number 222\n"<<flush;
          a.controlSayNumber(222);
          log << "Channel status: " << a.currentchannelStatus()<<endl<<flush;
          log<<"==================================================\n"<<flush;
          a.StreamFile("/tmp/testagi");
          a.hangupcurrentchanel();
          log.close();
          exit(0);
     } catch( exception e ) {
          // your handler
     }
}
