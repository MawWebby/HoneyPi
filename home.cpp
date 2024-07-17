//////////////////
// Dependencies //
//////////////////
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#define sleep Sleep

#else
#include <unistd.h>
#endif
#include <iostream>
#include <fstream>
using namespace std;




/////////////////
/// VARIABLES ///
/////////////////

// CONSTANT VARIABLES
const string honeyversion = "0.0.1";
const int heartbeattime = 10;

// SYSTEM VARIABLES
bool checkforupdates = false;
int startupchecks = 0;
int encounterederrors = 0;
bool attacked = false;
bool systemup = false;
int heartbeat = 0;
string erroroccurred = "";

// REPORT VARIABLES
bool generatingreport = false;
string pubip = "0.0.0.0";
int port = 0;
string usernames[101] = {};
string passwords[101] = {};
string keybinds[1000] = {};
string fileschanged[101] = {};
string fileactions[101] = {};



////////////////////////////////
//// DOCKER COMMANDS TO RUN ////
////////////////////////////////
const char* dockerstatuscommand = "docker ps";




////////////////////////////
// Send to Logger Scripts //
////////////////////////////
void sendtolog(string data2) {
    std::cout << data2 << std::endl;
}
void sendtologopen(string data2) {
    std::cout << data2;
}
void sendtologclosed(string data2) {
    std::cout << data2 << std::endl;
}
void loginfo(string data2) {
    data2 = "[INFO] - " + data2;
    sendtolog(data2);
}
void logwarning(string data2) {
    data2 = "[WARNING] - " + data2;
    sendtolog(data2);
}
void logcritical(string data2) {
    data2 = "[CRITICAL] - " + data2;
    sendtolog(data2);
}


//////////////////////////////
// REPORT GENERATING SCRIPT //
//////////////////////////////
int createreport() {
    logwarning("CREATING REPORT (THIS COULD TAKE SEVERAL MINUTES!)");

    sleep(5);


    // SAVE TO FILE
 //   myFile << "hello\n";

    return(1);

}



/////////////////////////
// THE MAIN CRASH LOOP //
/////////////////////////



////////////////////////////
// THE MAIN SETUP SCRIPTS //
//////////////////////////// 
void setup() {
    sendtolog("Hello, World");
    sendtolog("HoneyPi - MAIN Docker");
    sendtolog("Program by Matthew Whitworth (MawWebby)");
    sendtolog("Version #" + honeyversion);
    sendtolog("STARTING");
    
    // DELAY FOR SYSTEM TO START FURTHER
    sleep(5);



    sendtologopen("[INFO] - Verifying System...");

    // FUTURE LOOP OF INTEGRITY

    sendtologclosed("DONE (no checks needed)");
    


    sendtologopen("[INFO] - Checking for Updates...");

    if (checkforupdates == true) {

        // FUTURE LOOP OF UPDATING

    } else {
        sendtologclosed("disabled");
        logwarning("UNABLE TO CHECK FOR UPDATES! (SYSTEM DISABLED)");
    }


    
    // OPEN HACKING FILES
    sendtologopen("Opening Hacker File...");
//    fstream myFile;
 //   myFile.open("hackerlogv1.txt");

//    if (myFile.is_open() == false) {
 //       sendtologclosed("ERROR");
 //       startupchecks = startupchecks + 1;
 //   } else {
 //       sendtologclosed("DONE");
 //   }
    sendtologclosed("future");


    // CHECK DOCKER STATUS
    sendtologopen("Checking for Docker Control...");
    int output = system(dockerstatuscommand);
    if (output == 0) {
        sendtolog("Done");
    } else {
        sendtolog("ERROR");
        startupchecks = startupchecks + 1;
        logcritical("HoneyPi Docker is not priviledged!");
        logcritical("Could not communicate with docker");

    }

}

int main() {

    // SETUP LOOP
    setup();

    // STARTUP CHECKS
    if (startupchecks != 0) {
        logcritical("STARTUP CHECKS RETURNED EXIT CODE 1");
        logcritical("THE SYSTEM COULD NOT CONTINUE!");
        logcritical("ALL DOCKER CONTAINERS WILL BE STOPPED");

        // ADD FUTURE DOCKER CONTAINER INFORMATION


        // EXIT AND STOP PROCESSES
        return(1);
        return(1);
        return(1);
    }

    while(true && startupchecks == 0 && encounterederrors == 0) {
        
        if (attacked == false) {
            sleep(3);
        } else {
            sleep(1);
            logwarning("Guest VM has been attacked, reporting...");
        }

        if (heartbeattime <= heartbeat) {
            loginfo("heartbeat");
        } else {
            heartbeat = heartbeat + 1;
        }

        if (generatingreport = true) {
            encounterederrors = createreport();
        }
        
    }

    // ENCOUNTERED ERRORS
    if (encounterederrors != 0) {
        logcritical("HONEYPI HAS ENCOUNTERED UNRECOVERABLE ERRORS WHILE RUNNING!");
        logcritical("HONEYPI WILL NOW ATTEMPT A LOG DUMP!");
        std::cout << encounterederrors << std::endl;
        std::cout << erroroccurred << std::endl;

        std::cout << usernames << std::endl;
        std::cout << passwords << std::endl;
        std::cout << keybinds << std::endl;
        std::cout << fileschanged << std::endl;
        std::cout << fileactions << std::endl;
        std::cout << pubip << std::endl;
        std::cout << port << std::endl;
    }
}