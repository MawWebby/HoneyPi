#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#define sleep Sleep

#else
#include <unistd.h>
#endif


void setup() {
    printf("delay\n");
}

int main() {
    while(true) {
        
        printf("hello\n");
        sleep(3000000);
        
    }
}