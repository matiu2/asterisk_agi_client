/** \file  /usr/share/asterisk/agi-bin/hellowithClass.cpp
*    Description:  demo code for a call handling prg for asterisk basic agi functions
the  prg sends "orders to asterisk by writting AGI COMMANDS STREAM FILE, SEND IMAGE.... on the std ouput
asterisk will then reply on stdin of the prg  if command was succefull or failed see fct checkresult() has to be called after each call to asterisk
 Usage:
- Create an AGI  in /var/lib/asterisk/agi-bin, i.e.: compile with g++ hellowithClass.cpp  -o testagi

or in: /usr/share/asterisk/agi-bin
- set permission: chown asterisk:asterisk /var/lib/asterisk/agi-bin/testagi
 /etc/init.d/asterisk restart; rm /tmp/agireports.txt ;rm -rvf build/ ; mkdir build ; cd build ; cmake .. ; make testagiwithClass ; cd .. ; cp build/testagiwithClass ./testagi ; chown asterisk:asterisk ./testagi ; ./testagi < inputs  ; rm /tmp/agireports.txt
rm /tmp/agireports.txt ;rm -rvf build/ ; mkdir build ; cd build ; cmake .. ; make testagiwithClass ; cd .. ; cp build/testagiwithClass ./testagi ; chown asterisk:asterisk ./testagi

./testagi<inputs
- Call using EAGI from your dialplan: exten => 100,1,EAGI(restagi)
you can debug this agi script:
http://astbook.asteriskdocs.org/en/2nd_Edition/asterisk-book-html-chunk/asterisk-CHP-9-SECT-5.html
Debugging from the Operating System

As mentioned above, you should be able to run your program directly from the operating system to see how it behaves. The secret here is to act just like Asterisk does, providing your script with the following:

    A list of variables and their values, such as agi_test:1.

    A blank line feed (\n) to indicate that you’re done passing variables.

    Responses to each of the AGI commands from your AGI script. Usually, typing 200 response=1 is sufficient.

Trying your program directly from the operating system may help you to more easily spot bugs in your program.
you can automate this runing ./testagi <inputs
debian-asterisk:/usr/share/asterisk/agi-bin# cat inputs
 agi_test:1

200 response=1


debian-asterisk:/usr/share/asterisk/agi-bin#
 *\version  1.0
 *\date 01/12/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  Lyase Damasked
 *        Company:
 *set debug option in asterisk console with: agi set debug on
*
 * =====================================================================================
 */
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
using namespace std ;
typedef unsigned short Code;
typedef unsigned char Digit;




int main ()
{
    try {
        ofstream mylogfile;
        mylogfile.open ("/tmp/agireports.txt");
        ofstream tosrvlogfile;
        tosrvlogfile.open ("/tmp/CommandsSentToAsterisk.txt");
        AsteriskCallProxy a(cin, cout,mylogfile);
        a.readConfig();
        Command* anOrder ;
        anOrder= new CommandSayNumber(a, 111);
        anOrder->Execute();
        mylogfile<<a;
        using std::cerr;
        using std::endl;
        mylogfile<<" answer call now\n"<<flush;
        a.answer();
        mylogfile<<" \n controlStreamFile\n"<<flush;
        //     a.StreamFile("/tmp/testagi");
        //a.controlStreamFile("/tmp/testagi");
        mylogfile<<" \n now: say number 1111\n"<<flush;
        a.controlSayNumber(111);
        std::cerr << "Channel status: " << a.currentchannelStatus()<<endl<<flush;
        mylogfile<<" \nnow:  say number 222\n"<<flush;
        a.controlSayNumber(222);
        std::cerr << "Channel status: " << a.currentchannelStatus()<<endl<<flush;
        mylogfile<<"==================================================\n"<<flush;
        a.StreamFile("/tmp/testagi");
        //a.hangupcurrentchanel(); does not work on result
        mylogfile.close();
        exit(0);
    } catch( exception e ) {
        exit(0);
    }       // your handler
}
/*
ancien main
int resultcode=0;
Agi_env agi(cin, cout, );
agi.dump_agi();
mylogfile << " logging to global file "<<resultcode <<".\n"<<flush;

mylogfile<< "4. Testing 'saynumber'...\n"<<flush;
resultcode=agi.SayNumber(192837466);
 mylogfile << "I  said a number the asterisk replied  result is:\""<<resultcode <<"\".\n if 0 maybe the initial value not returned code from server\n"<<flush;

/*
// command to send text msg to current call
resultcode =agi.SendText( "hello world");

// command to send an image  to current call
resultcode =agi.SendImage( "asterisk-image");
// command to read number to  current call

// command to read user input will return ascii code of first digit enteredby  current call
fprintf( stderr, "5. Testing 'waitdtmf'...\n");

resultcode =agi.GetDigit( -1);
mylogfile << "reading dtmf I got from dtmf following code:"<<resultcode <<".\n"<<flush;


mylogfile<<  "main() Testing playback...\n";
resultcode =agi.StreamFile("beep");
resultcode=agi.Getnumber3Digit(-1);
resultcode=agi.SayNumber(resultcode);
resultcode =agi.StreamFile("beep");
resultcode =agi.StreamFile("/tmp/testagi");
// command to record sound message of 30s or until user hits keyboard in  current call
//default location for file is usr/share/asterisk/sounds/testagi.gsm
// [Dec  2 06:18:23] WARNING[12108]: file.c:1160 ast_writefile: Unable to open file /usr/share/asterisk/sounds/testagi.gsm: Permission denied
//change volume sox -v 2.0 /tmp/testagi.gsm testagi.gsm


mylogfile<< "\n main() Testing 'record'...\n";
resultcode =agi.recordFile("/tmp/testagi","gsm",30000,11);
fflush(stdout);
// command to playback sound file to  current call
mylogfile<< "\n main() 6a. Testing 'record' playback...\n"<<flush;
resultcode =agi.StreamFile("/tmp/testagi");
fflush(stdout);
:resultcode = agi.checkresult();
mylogfile<<"================== Complete ======================\n"<<flush;
mylogfile\
<< agi.nbrcommandsent()\
<< " tests sent ,"\
<<agi.nbrcommandok()\
<<" passed,"\
<<agi.nbrcommandfail()\
<<" failed\n"<<flush;
mylogfile<<"==================================================\n"<<flush;
agi.hangup();
mylogfile.close();
exit(0);
*/


