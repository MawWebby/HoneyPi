#include <iostream>
#include <string>
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif
#include <iostream>
#include <fstream>
#include <thread>
#define PORT 63599
#include <ctime>

int main() {

}