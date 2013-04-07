#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BACKLOG 10

void handleerr(int d);
void printerror(int err);

void handleerr(int d) {
    if(d == -1) {
        printerror(errno);
        exit(1);
    }
}

void printerror(int err) {
    printf("Error is %d: %s\n", errno, strerror(errno));
}

