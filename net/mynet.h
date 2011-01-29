#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 1000
#define MAXQLEN 10

typedef void sigfunc(int);

void handleerr(int d);
void handleerr_s(char *mes);
void printerror(int err);
void printerror_s(char *mes);
void startserver(void (*func)(int d), int port);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);
static ssize_t my_read(int fd, char *ptr);
static ssize_t readline(int fd, void *vptr, size_t maxlen);
void register_signal_handler(int signum, sigfunc * func);

