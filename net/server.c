#include "mynet.h"

void stuff(int);

void stuff(int connfd) {
    char buff[MAXLINE] = "Hello";
    write(connfd, buff, strlen(buff));
}

int main(int argc, char **argv) {
    startserver(stuff);
}
