//////////////////
// Dependencies //
//////////////////
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#include <corecrt_io.h>
#define sleep Sleep

#else
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#endif
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;




/////////////////
/// VARIABLES ///
/////////////////

// CONSTANT VARIABLES
const string honeyversion = "0.0.2";
const int heartbeattime = 10;

// SYSTEM VARIABLES
bool checkforupdates = true;
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

// NETWORK VARIABLES
const int serverport1 = 63599;
const int serverport2 = 9090;
const int serverport3 = 11520;
const int BUFFER_SIZE = 1024;
int serverSocket1 = 0;
int serverSocket2 = 0;
int server_fd, new_socket;
bool packetactive = false;
char buffer[1024] = {0};



////////////////////////////////
//// DOCKER COMMANDS TO RUN ////
////////////////////////////////
const char* dockerstatuscommand = "docker ps > nul:";
const char* dockerstartguestssh = "docker run -itd --rm --network=my-network1 --name=SSHVMV1 honeypotpi:guestsshv1 > nul:";
//const char* serverport63599script = "system(./test)";

int serverport63599script() {
    system("./test");
    return 0;
}

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



int dictionary() {
    if (attacked == false) {
        if (buffer == "heartbeatSSH") {
            loginfo("Received Heartbeat from SSH");
            return 0;
        }

        if (buffer == "attack") {
            logwarning("Attack detected on SSH, logging");
            attacked = true;
        }
    } else {
        // ATTACKED RUN ATTACKED COMMANDS!
        
        return 0;

    }
}


void listenon63599() { 
    read(new_socket, buffer, 1024);
    if (buffer != NULL) {
        std::cout << "check" << std::endl;
        std::cout << buffer << std::endl;
        std::cout << "|" << std::endl;
        packetactive = false;
        dictionary();
    }
    return;
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
int setup() {
    sendtolog("Hello, World");
    sendtolog("HoneyPi - MAIN Docker");
    sendtolog("Program by Matthew Whitworth (MawWebby)");
    sendtolog("Version #: " + honeyversion);
    
    // DELAY FOR SYSTEM TO START FURTHER
    sleep(5);



    // DETERMINE NETWORK CONNECTIVITY
    sendtologopen("[INFO] - Determining Network Connectivity...");
    int learnt = system("ping -c 5 8.8.8.8 > nul:");
    if (learnt == 0) {
        sendtologclosed("Done");
    } else {
        sendtologclosed("ERROR");
        logcritical("UNABLE TO DETERMINE NETWORK CONNECTIVITY!");
        logcritical("Killing");
        startupchecks = startupchecks + 1;
        return 1;
        return 1;
        return 1;
    }




    sendtologopen("[INFO] - Verifying System...");

    // FUTURE LOOP OF INTEGRITY

    sendtologclosed("DONE (no checks needed)");
    



    // CHECK FOR SYSTEM UPDATES
    sendtologopen("[INFO] - Checking for Updates...");
    if (checkforupdates == true) {
        // CHECK FOR SYSTEM UPDATES
        int returnedvalue = system("apt-get update > nul:");
        if (returnedvalue == 0) {
            sendtologclosed("Done");
        } else {
            sendtologclosed("ERROR");
            logcritical("UNABLE TO CHECK FOR SYSTEM UPDATES!");
            logcritical("This could be potentially dangerous!");
            logcritical("KILLING PROCESS!");
            startupchecks = startupchecks + 1;
            return 1;
            return 1;
            return 1;
        }



        // CHECK FOR SYSTEM UPDATES
        sendtologopen("[INFO] - Updating System...");
        int returnedvalue2 = system("apt-get upgrade -y > nul:");
        if (returnedvalue2 == 0) {
            sendtologclosed("Done");
        } else {
            sendtologclosed("ERROR");
            logcritical("UNABLE TO UPGRADE SYSTEM!");
            logcritical("This could be potentially dangerous!");
            logcritical("KILLING PROCESS!");
            startupchecks = startupchecks + 1;
            return 1;
            return 1;
            return 1;
        }

    } else {
        sendtologclosed("disabled");
        logwarning("UNABLE TO CHECK FOR UPDATES! (SYSTEM DISABLED)");
    }


    
    // OPEN HACKING FILES
    sendtologopen("[INFO] - Opening File...");
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
    sendtologopen("[INFO] - Checking for Docker Control...");
    sleep(1);
    int output = system(dockerstatuscommand);
    if (output == 0) {
        sendtolog("Done");
    } else {
        sendtolog("ERROR");
        startupchecks = startupchecks + 1;
        logcritical("HoneyPi Docker is not priviledged!");
        logcritical("Could not communicate with docker");
        return 1;
        return 1;
        return 1;
    }


    int PORT = 63599;

    // OPEN NETWORK SERVER PORTS (1/2)
    sendtologopen("[INFO] - Opening Server Ports (1/2).");
 //   std::thread t2{serverport63599script};
    std::cout << "Hello message sent" << std::endl;

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    std::string hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // REACHED HERE

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if (accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "NetworkPortDeclared" << std::endl;

    sendtologclosed("Done");
    sleep(2);





    sendtologopen("[INFO] - Creating server thread on port listen...");

    sleep(2);
    std::thread t1{listenon63599};
    t1.detach();
    packetactive = true;
    sleep(1);
    sendtologclosed("Done");



    // OPEN NETWORK SERVER PORTS (2/2)
    sendtologopen("[INFO] - Opening Server Ports (2/2)...");
    sleep(2);
    




    // START GUEST DOCKER CONTAINER FOR SSH
    sendtologopen("[INFO] - Starting Guest Docker Container (SSH) - ");
    sleep(2);
    int status = system(dockerstartguestssh);



    // SYSTEM STARTED
    sendtolog("[INFO] - Updating API Token...");


    // FUTURE NETWORK COMMUNICATION TO UPDATE API TOKENS

    sendtolog("future");

    
    
    return 0;

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
        close(serverport1);
        close(serverport2);
        sleep(10);
        int completion = system("docker kill *");
        sleep(10);

        // EXIT AND STOP PROCESSES
        return(1);
        return(1);
        return(1);
    }

    loginfo("Main system has started successfully");
    loginfo("Waiting for Heartbeat from VM");

    // NETWORK INFORMATION
    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // MAIN RUNNING LOOP
    while(true && startupchecks == 0 && encounterederrors == 0) {
        
        if (attacked == false) {
            sleep(3);
        } else {
            sleep(1);
            logwarning("Guest VM has been attacked, reporting...");
        }

        std::cout << "test" << std::endl;
        sleep(2);

        if (packetactive == false) {
            std::thread t1{listenon63599};
            t1.detach();
            packetactive = true;
        }

        if (heartbeattime <= heartbeat) {
            loginfo("heartbeat");
        } else {
            heartbeat = heartbeat + 1;
        }

        if (generatingreport == true) {
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

        logcritical("ATTEMPTING TO KILL ALL DOCKER CONTAINERS!!!");
        close(serverport1);
        close(serverport2);
        sleep(10);
        int completion = system("docker kill *");
        sleep(10);
    }
}