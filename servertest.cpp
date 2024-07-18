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

char buffer[1024] = {0};
int server_fd, new_socket;

void listenon63599() { 
    read(new_socket, buffer, 1024);
}

int main() {
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
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    
    while(true) {
        std::cout << "test" << std::endl;
        std::thread t{listenon63599};
        
        if (buffer != NULL) {
            std::cout << buffer << std::endl;
        }
        std::cout << buffer << std::endl;
    }
    send(new_socket, hello.c_str(), hello.size(), 0);
    std::cout << "Hello message sent" << std::endl;
    close(new_socket);
    close(server_fd);
    return 0;
}
