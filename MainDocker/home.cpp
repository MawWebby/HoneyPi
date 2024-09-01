//////////////////
// Dependencies //
//////////////////
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include <map>

const bool debug = false;
const bool testing = false;



/////////////////
/// VARIABLES ///
/////////////////

// CONSTANT VARIABLES
const std::string honeyversion = "0.0.2";
const int heartbeattime = 10;

// SYSTEM VARIABLES
bool checkforupdates = true;
int startupchecks = 0;
int encounterederrors = 0;
bool attacked = false;
bool systemup = false;
int heartbeat = 29;
std::string erroroccurred = "";
int packetsreceivedSSH = 0;
int packetsreceivedAPI = 0;
bool heartbeatreceivedrsttimeSSH = false;

// DOCKER VARIABLES
int timesincelastcheckinSSH = 0;
long int lastcheckinSSH = 0;


// REPORT VARIABLES - SSH
bool SSHDockerActive = false;
bool generatingreportSSH = false;
std::string pubipSSH = "0.0.0.0";
int portSSH = 0;
std::string usernamesSSH[101] = {};
std::string passwordsSSH[101] = {};
std::string keybindsSSH[1000] = {};
std::string fileschangedSSH[101] = {};
std::string fileactionsSSH[101] = {};
std::string pubkeysSSH[101] = {};
std::string prikeysSSH[101] = {};
std::string commandsrunSSH[1001] = {};

// NETWORK VARIABLES
const int serverport1 = 63599;
const int serverport2 = 9090;
const int serverport3 = 11520;
const int BUFFER_SIZE = 1024;
int serverSocket1 = 0;
int serverSocket2 = 0;
int serverSocket3 = 0;
int server_fd, new_socket;
int port1;
int server_fd2, new_socket2;
int server_fd3, new_scoket3;
bool packetactive = false;

// TIME VARIABLES
long long int startuptime = 0;
long long int currenttime = 0;
long long int timesincestartup = 0;
int currenthour = 0;
int currentminute = 0;
int currentsecond = 0;
int currentdayofyear = 0;
int currentdays = 0;
int currentyear = 0;
int currentmonth = 0;
int secondsperyear = 31536000;
int daysperyear = 365.25;
int secondsperday = 86400;
int secondsperhour = 3600;
int secondsperminute = 60;
int minutesperhour = 60;
int hoursperday = 24;
bool calculatingtime = false;

// FILE LOCATIONS
const char* SSHStreamFile = "/home/sshfile.txt";
const char* SSHEncryptedFile = "/home/encryptedssh.txt";


// PORT BLOCKING VARIABLES
std::map<int, int> blockportdictionary = {
    {0, 9000},
    {1, 9001},
    {2, 9002},
    {3, 9003},
    {4, 9004},
    {5, 9005},
    {6, 9006},
    {7, 9007},
    {8, 9008},
    {9, 9009},
    {10, 9010},
};
std::map<int, int> sendportdictionary = {
    {0, 9010},
    {1, 9011},
    {2, 9012},
    {3, 9013},
    {4, 9014},
    {5, 9015},
    {6, 9016},
    {7, 9017},
    {8, 9018},
    {9, 9019},
    {10, 9020},
};
std::map<int, int> serverSocketdictionary = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
};
std::map<int, int> server_fddictionary = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
};
std::map<int, int> new_socketdictionary = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
};
std::map<int, bool> serverportsactive = {
    {0, false},
    {1, false},
    {2, false},
    {3, false},
    {4, false},
    {5, false},
    {6, false},
    {7, false},
    {8, false},
    {9, false},
    {10, false},
};


long long int timers[10] = {};
// 0 - RESTART SSH DOCKER VARIABLE
// 1 - TIMER TO STOP BUFFER OVERFLOW ON SSH (63599) DOCKER AND CAUSE CPU CRASH
// 2 - TIMER TO STOP BUFFER OVERFLOW ON ROUTER API (11535) PORT





////////////////////////////////
//// DOCKER COMMANDS TO RUN ////
////////////////////////////////
const char* dockerstatuscommand = "docker ps > nul:";
const char* dockerstartguestssh = "docker run -itd --rm --name=SSHVMV1 -p 22:22 --network=my-network1 honeypotpi:guestsshv1 > nul:";
const char* dockerstartguestsshNOREMOVE = "docker run -itd --name=SSHVMV1 -p 22:22 --network=my-network1 honeypotpi:guestsshv1 > nul:";
const char* dockerkillguestssh = "docker container kill SSHVMV1 > nul:";
const char* dockerremoveguestssh = "docker container rm SSHVMV1 > nul:";








int timedetector() {
    if (calculatingtime == true) {
        std::cout << "[WARNING] - Call to Time Calculation Called While Already Processing!" << std::endl;
        return 1;

    }  else {
        // TIME
        currenttime = time(NULL);

        // CURRENT SECONDS
        timesincestartup = currenttime - startuptime;
        currentsecond = currenttime % secondsperminute;

        // CURRENT MINUTES
        currentminute = currenttime - currentsecond;
        currentminute = currentminute % 3600;
        currentminute = currentminute / 60;

        // CURRENT HOURS
        currenthour = currenttime - ((currentminute * 60) + currentsecond);
        currenthour = currenthour % hoursperday;
        
        // CURRENT DAYS
        currentdays = currenttime - ((currenthour * 3600) + (currentminute * 60) + currentsecond);
        currentdays = currentdays / 86400;

        // CURRENT YEARS
        currentyear = 1970 + (currentdays / 365.25);

        // DEBUG PRINT VALUES TO CONSOLE
        if (debug == true) {
            std::cout << currentsecond << std::endl;
            std::cout << currentminute << std::endl;
            std::cout << currenthour << std::endl;
            std::cout << currentdays << std::endl;
            std::cout << currentyear << std::endl;
        }

        return 0;
    }

    return 1;
}








////////////////////////////
// Send to Logger Scripts //
////////////////////////////
void sendtolog(std::string data2) {
    std::cout << data2 << std::endl;
}
void sendtologopen(std::string data2) {
    std::cout << data2;
}
void sendtologclosed(std::string data2) {
    std::cout << data2 << std::endl;
}
void loginfo(std::string data2) {
    data2 = "[INFO] - " + data2;
    sendtolog(data2);
}
void logwarning(std::string data2) {
    data2 = "[WARNING] - " + data2;
    sendtolog(data2);
}
void logcritical(std::string data2) {
    data2 = "[CRITICAL] - " + data2;
    sendtolog(data2);
}










//////////////////////////////////////////
// HANDLE NETWORKED CONNECTIONS (63599) //
//////////////////////////////////////////
void handleConnections(int server_fd) { 
    char buffer[1024] = {0};
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int new_socket;
    ssize_t valread;
    std::string hello = "Hello from server";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        if (SSHDockerActive == false) {
            logcritical("SSH Docker Container Dead, Closing Port");
            return;
        }
        perror("accept");
        exit(EXIT_FAILURE);
    }

    timers[1] = time(NULL);

    while(SSHDockerActive == true) {
        read(new_socket, buffer, 1024);
        if (debug == true) {
            sendtologopen(buffer);
        }

        loginfo(buffer);

        if (buffer != NULL && attacked == false) {

            
            // HEARTBEAT COMMAND TO NOT SPAM LOG
            if (strcmp(buffer, "heartbeatSSH") == 0) {
                lastcheckinSSH = time(NULL);
                if (heartbeat >= 30) {
                    loginfo("Received heartbeat from SSH Guest VM");
                    heartbeat = 0;
                } else {
                    heartbeat = heartbeat + 1;
                }
                SSHDockerActive = true;
            }

            if(strcmp(buffer, "attacked") == 0) {
                logwarning("SSH attacked! - Logging...");
            }

        } else {
            if (buffer != NULL && attacked == true) {

                // ADD COMMANDS HERE OF BEING ATTACKED AND STORING THAT DATA

            } else {
                if (buffer == NULL) {
                    logcritical("INVALID CONNECTION RECEIVED, ignoring...");
                }
            }
        }

        // Send a hello message to the client
//        send(new_socket, hello.c_str(), hello.size(), 0);
//        std::cout << "Hello message sent" << std::endl;

        if (SSHDockerActive == false) {
            logcritical("No SSH Docker Container/Killing Thread");
        }

        // ANTI-CRASH PACKET FLOW CHECK
        if (timers[1] == time(NULL)) {
            packetsreceivedSSH = packetsreceivedSSH + 1;
            if (packetsreceivedSSH >= 10) {
                // KILL CONTAINER
                logcritical("PACKET OVERFLOW DETECTED ON SSH DOCKER PORT!/KILLING THREAD AND CONTAINER!");
                close(server_fd);
                timers[0] = time(NULL);
                SSHDockerActive = false;
                system(dockerkillguestssh);
                sleep(3);
                system(dockerremoveguestssh);
            }
        } else {
            timers[1] = time(NULL);
            packetsreceivedSSH = 0;
        }
    }
}





//////////////////////////////////////////
// HANDLE NETWORKED CONNECTIONS (11535) //
//////////////////////////////////////////
void handle11535Connections(int server_fd2) {
    char buffer[1024] = {0};
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int new_socket2;
    ssize_t valread;
    std::string hello = "Hello from server";

    if ((new_socket2 = accept(server_fd2, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    } else {
        loginfo("11535 port initialized");
    }

    while(true) {
        read(new_socket2, buffer, 1024);
        sendtologopen(buffer);

        if (buffer != NULL && attacked == false) {

            // HEARTBEAT COMMAND TO NOT SPAM LOG
            if (strcmp(buffer, "heartbeatSSH")) {
                if (heartbeat >= 10) {
                    loginfo("Received heartbeat from SSH Guest VM");
                } else {
                    heartbeat = heartbeat + 1;
                }
            } 

        } else {
            if (buffer != NULL && attacked == true) {

            } else {
                if (buffer == NULL) {
                    logcritical("INVALID CONNECTION RECEIVED, ignoring...");
                }
            }
        }


        // ANTI-CRASH PACKET FLOW CHECK
        if (timers[2] == time(NULL)) {
            packetsreceivedAPI = packetsreceivedAPI + 1;
            if (packetsreceivedAPI >= 10) {
                // KILL CONTAINER
                logcritical("PACKET OVERFLOW DETECTED ON ROUTER API!");
                close(server_fd2);
            }
        } else {
            timers[2] = time(NULL);
            packetsreceivedAPI = 0;
        }



 //        Send a hello message to the client
         send(new_socket2, hello.c_str(), hello.size(), 0);
         std::cout << "Hello message sent" << std::endl;
    }
}


/////////////////////////////////////////
// HANDLE NETWORKED CONNECTIONS (8080) // 
/////////////////////////////////////////
void handle8080Connections(int server_fd3) {

}




//////////////////////////////
// REPORT GENERATING SCRIPT //
//////////////////////////////
int createreport() {
    logwarning("CREATING REPORT (THIS COULD TAKE SEVERAL MINUTES!)");

    sleep(5);

    // OPEN FILE
    std::ifstream inputStream;
    inputStream.open(SSHStreamFile);
    std::ofstream encryptedStream;
    encryptedStream.open(SSHEncryptedFile);
    if (inputStream.is_open() != true && encryptedStream.is_open() != true) {
        logcritical("AN ERROR OCCURRED WITH THE SSH FILE!");
        logcritical("COULD NOT CONTINUE");
        encounterederrors = encounterederrors + 1;
        return 1;
        return 1;
    } else {
        std::string inputstring;
        std::string encryptedstring;
        std::string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::string compressedkey = "zxywv";
        encryptedStream << compressedkey << '\n';
        int testtastic = 0;
        int testtasticmax = 5;
        bool completion31 = false;
        while (completion31 != true) {
            getline(inputStream, inputstring);
            if (inputstring == "") {
                testtastic = testtastic + 1;
                if (testtastic >= testtasticmax) {
                    completion31 = true;
                }
            } else {
                int hat = 0;
                while (inputstring.length() >= hat) {
                    // HAT TWO THIRTY
                }
            }
        }

        // SEND TO SERVER!
    }

    return 1;
}










int createnetworkport63599() {
    int PORT = 63599;
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    std::string hello = "Hello from server";
    int opt = 1;

    // SETUP NETWORK PORTS
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 63599
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // REACHED HERE
    sendtologopen("...");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the network address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}



/////////////////////////
// THE MAIN CRASH LOOP //
/////////////////////////





////////////////////////////
// THE MAIN SETUP SCRIPTS //
//////////////////////////// 
int setup() {
    sendtolog("Hello, World from 2515!");
    sendtolog("  _____     _____     ____________      _____      ____  ________________   ____         ____           ______________     ________________  ");
    sendtolog("  |   |     |   |    /            `     |   `      |  |  |               |  `  `        /   /           |             `   |               |  ");
    sendtolog("  |   |     |   |   /              `    |    `     |  |  |  |¯¯¯¯¯¯¯¯¯¯¯¯    `  `      /   /            |   |¯¯¯¯¯¯`   |  |_____    ______|  ");
    sendtolog("  |   |     |   |  /   /¯¯¯¯¯¯¯¯`   `   |     `    |  |  |  |____________     `  `    /   /             |   |______/   |        |   |        ");
    sendtolog("  |    ¯¯¯¯¯    |  |   |         |   |  |      `   |  |  |               |     `  `  /   /              |   __________/         |   |        ");
    sendtolog("  |    _____    |  |   |         |   |  |   |`  `  |  |  |               |      `  `/   /               |   |                   |   |        ");
    sendtolog("  |   |     |   |  |   |         |   |  |   | `  ` |  |  |  |¯¯¯¯¯¯¯¯¯¯¯¯        |     |                |   |                   |   |        ");
    sendtolog("  |   |     |   |  |   |         |   |  |   |  `  `|  |  |  |____________        |     |                |   |                   |   |        ");
    sendtolog("  |   |     |   |  `   `¯¯¯¯¯¯¯¯¯    /  |   |   `     |  |               |       |     |                |   |             |¯¯¯¯¯     ¯¯¯¯¯|  ");
    sendtolog("  |   |     |   |   `               /   |   |    `    |  |               |       |     |                |   |             |               |  ");
    sendtolog("  ¯¯¯¯¯     ¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯      `¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯        ¯¯¯¯¯¯                 ¯¯¯¯¯             ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯   ");
    sendtolog("SERVER EDITION!");
    sendtolog("");
    sendtolog("");
    sendtolog("");
    sendtolog("");
    sendtolog("");
    sendtolog("Program by Matthew Whitworth (MawWebby)");
    sendtolog("Version: " + honeyversion);
    sendtolog("");
    sendtolog("");
    sendtolog("");
    sendtolog("");
    sendtolog("");
    
    // DELAY FOR SYSTEM TO START FURTHER (FIGURE OUT CURRENT TIME)
    sleep(4);

    loginfo("Starting");

    startupchecks = startupchecks + timedetector();


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
        logcritical("Could not communicate with docker");
        return 1;
        return 1;
        return 1;
    }







    int PORT = 63599;

    // OPEN NETWORK SERVER PORTS (1/3)
    sendtologopen("[INFO] - Opening Server Ports (1/3)");

    port1 = createnetworkport63599();

    sendtologclosed("Done");
    sleep(2);




    sleep(3);
    PORT = 11535;

    // OPEN NETWORK SERVER PORTS (2/3)
    sendtologopen("[INFO] - Opening Server Ports (2/3)...");

    int server_fd2, new_socket2;
    ssize_t valread2;
    struct sockaddr_in address2;
    socklen_t addrlen2 = sizeof(address2);
    int opt2 = 1;
    
    sleep(1);

    if((server_fd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 11535
    if (setsockopt(server_fd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt2, sizeof(opt2))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // REACHED HERE
    sendtologopen("...");
    address2.sin_family = AF_INET;
    address2.sin_addr.s_addr = INADDR_ANY;
    address2.sin_port = htons(PORT);

    // Binding the socket to the network address and port
    if (bind(server_fd2, (struct sockaddr*)&address2, sizeof(address2)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd2, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    sendtologclosed("Done");
    sleep(2);





    // SERVER PORT LISTEN THREAD (2/3) (11535)
    sendtologopen("[INFO] - Creating server thread on port 11535 listen...");

    sleep(2);
    std::thread acceptingClientsThread2(handle11535Connections, server_fd2);
    acceptingClientsThread2.detach();
    sleep(1);

    sendtologclosed("Done");






    // START GUEST DOCKER CONTAINER FOR SSH
    sendtologopen("[INFO] - Starting Guest Docker Container (SSH) - ");
    sleep(2);
    int status;

    if (debug == true) {
        status = system(dockerstartguestsshNOREMOVE);
    } else {
        status = system(dockerstartguestssh);
    }

    if (status == 0) {
        SSHDockerActive = true;
        lastcheckinSSH = time(NULL) + 10;
        sendtologclosed("Done");
    } else {
        status = system(dockerkillguestssh);
        sleep(3);
        status = system(dockerremoveguestssh);
        sleep(1);
        status = system(dockerstartguestssh);

        if (status == 0) {
            SSHDockerActive = true;
            lastcheckinSSH = time(NULL) + 10;
            sendtologclosed("Done");
        } else {
            SSHDockerActive = false;
            lastcheckinSSH = 0;
            logcritical("SSH DOCKER DID NOT START SUCCESSFULLY");
        }
    }



    // SYSTEM STARTED
    sendtologopen("[INFO] - Updating API Token...");


    // FUTURE NETWORK COMMUNICATION TO UPDATE API TOKENS

    sendtolog("future");

    sendtologopen("[INFO] - Starting Port Blocking Service!");

    
    
    return 0;
}






int main() {

    // SETUP LOOP
    setup();

    // SERVER PORT LISTEN THREAD
    sendtologopen("[INFO] - Creating server thread on port 63599 listen...");

    sleep(2);
    std::thread acceptingClientsThread(handleConnections, port1);
    acceptingClientsThread.detach();
    sleep(1);

    sendtologclosed("Done");

    // STARTUP CHECKS
    if (startupchecks != 0) {
        logcritical("STARTUP CHECKS RETURNED EXIT CODE 1");
        logcritical("THE SYSTEM COULD NOT CONTINUE!");
        logcritical("ALL DOCKER CONTAINERS WILL BE STOPPED");

        // ADD FUTURE DOCKER CONTAINER INFORMATION
        close(serverport1);
        close(serverport2);
        sleep(10);
        int completion = system("docker kill * > nul:");
        sleep(10);

        // EXIT AND STOP PROCESSES
        return(1);
        return(1);
        return(1);
    }

    

    if (testing == true) {
        sendtologopen("[INFO] - Beta Testing Active...");
        sleep(1);
        sendtologclosed("Nothing to Test");
    } else {
        sendtolog("[INFO] - Not beta testing/Removing beta file...");
        startupchecks = startupchecks + system("rm test");
    }

    loginfo("Main HoneyPi has started successfully");

    // NETWORK INFORMATION
    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // MAIN RUNNING LOOP
    while(true && startupchecks == 0 && encounterederrors == 0) {

        if (attacked == false) {
            sleep(2);
        } else {
            sleep(0.25);
            logwarning("Guest VM has been attacked, reporting...");
        }

        if (generatingreportSSH == true) {
            encounterederrors = encounterederrors + createreport();
        }


        // WATCHDOG IN MAIN LOOP
        int differenceintimeSSH = time(NULL) - lastcheckinSSH;
        if (SSHDockerActive == true) {
            if (heartbeatreceivedrsttimeSSH == true) {
                if (differenceintimeSSH >= 30) {
                    logwarning("30 seconds since last SSH Heartbeat received");
                }

                if (differenceintimeSSH >= 45) {
                    logcritical("45 seconds since last SSH Heartbeat received, assuming dead");
                    close(server_fd);
                    SSHDockerActive = false;
                    system(dockerkillguestssh);
                    sleep(3);
                    system(dockerremoveguestssh);
                    timers[0] = time(NULL);
                }
            } else {
                if (differenceintimeSSH >= 240) {
                    logwarning("240 seconds since first expected SSH Heartbeat received");
                }

                if (differenceintimeSSH >= 300) {
                    logcritical("300 seconds since first expected SSH Heartbeat received, assuming dead");
                    close(server_fd);
                    SSHDockerActive = false;
                    system(dockerkillguestssh);
                    sleep(3);
                    system(dockerremoveguestssh);
                    timers[0] = time(NULL);
                }
            }
            
        } else {
            if (timers[0] != 0) {
                long long int changeintime = time(NULL) - timers[0];

                if (changeintime >= 60) {
                    logwarning("Attempting to restart SSH VM");
                    system(dockerkillguestssh);
                    sleep(3);
                    system(dockerremoveguestssh);
                    sleep(3);
                    system(dockerstartguestssh);
                    SSHDockerActive = true;
                    lastcheckinSSH = time(NULL) + 10;
                    port1 = createnetworkport63599();
                    sleep(2);
                    std::thread acceptingClientsThread(handleConnections, port1);
                    acceptingClientsThread.detach();
                }
            } else {
                logwarning("Attempting to restart in 60 seconds!");
                timers[0] = time(NULL);
            }
        }

    }

    // ENCOUNTERED ERRORS
    if (encounterederrors != 0) {
        logcritical("HONEYPI HAS ENCOUNTERED UNRECOVERABLE ERRORS WHILE RUNNING!");
        logcritical("HONEYPI WILL NOW ATTEMPT A LOG DUMP!");
        std::cout << encounterederrors << std::endl;
        std::cout << erroroccurred << std::endl;


        std::cout << usernamesSSH << std::endl;
        std::cout << passwordsSSH << std::endl;
        std::cout << keybindsSSH << std::endl;
        std::cout << fileschangedSSH << std::endl;
        std::cout << fileactionsSSH << std::endl;
        std::cout << pubipSSH << std::endl;
        std::cout << portSSH << std::endl;
        std::cout << pubkeysSSH << std::endl;
        std::cout << prikeysSSH << std::endl;


        logcritical("ATTEMPTING TO KILL ALL DOCKER CONTAINERS!!!");
        close(serverport1);
        close(serverport2);
        sleep(10);
        int completion = system("docker kill * > nul:");
        sleep(10);
    }
}