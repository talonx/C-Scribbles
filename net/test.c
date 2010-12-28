#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char* add = "192.168.1.160";
    struct in_addr* addr = (struct in_addr*)malloc(sizeof(struct in_addr*));
    int res = inet_pton(AF_INET, add, addr);
    printf("%d\n", res);
   
    char resadd[INET_ADDRSTRLEN];
    const char* result = inet_ntop(AF_INET, addr, resadd, INET_ADDRSTRLEN);
    printf("%s\n", result); 
    printf("%s\n", resadd); 
}

