#include "nethelper.h"
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void printit(struct addrinfo *);
void * get_in_addr(struct sockaddr *);

void sigchld_handler(int s) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char **argv) {

    int yes = 1;

    int res;
    const char* node  = argv[1];
    char clientinfo[INET6_ADDRSTRLEN];

    char *mes = "Humma magrumammammaheyo hummam magurumma";
    int mlen = strlen(mes);
    //const char* service = NULL;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct sigaction sag;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    res = getaddrinfo(node, "8080", &hints, &servinfo);

    handleerr(res);

    printit(servinfo);

    int fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    handleerr(fd);

    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    int bindres = bind(fd, servinfo->ai_addr, servinfo->ai_addrlen);
    handleerr(bindres);

    //   int cres = connect(fd, servinfo->ai_addr, servinfo->ai_addrlen);
    //   handleerr(cres);

    freeaddrinfo(servinfo);

    int lres = listen(fd, BACKLOG);
    handleerr(lres);

    sag.sa_handler = sigchld_handler;
    sigemptyset(&sag.sa_mask);
    sag.sa_flags = SA_RESTART;
    int sin = sigaction(SIGCHLD, &sag, NULL);
    handleerr(sin);


    struct sockaddr_storage clientaddr;
    socklen_t len = sizeof (struct sockaddr_storage);

    while(1) {
        printf("Accepting connections...\n");

        int connfd = accept(fd, (struct sockaddr *)&clientaddr, &len);
        handleerr(connfd);

        inet_ntop(clientaddr.ss_family, get_in_addr((struct sockaddr *)&clientaddr), clientinfo, sizeof clientinfo);
        printf("Got connection from %s\n", clientinfo);

        if(!fork()) {//Child process
            close(fd);

            int bytes_sent;
            bytes_sent = send(connfd, mes, mlen, 0);
            handleerr(bytes_sent);
            printf("Bytes sent %d\n", bytes_sent);
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}

void * get_in_addr(struct sockaddr *sa) {
    if(sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void printit(struct addrinfo *servinfo) {
    struct addrinfo *p;
    char ipstr[INET6_ADDRSTRLEN];

    for (p = servinfo; p!= NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        if(p->ai_family == AF_INET) {
            struct sockaddr_in *sa = (struct sockaddr_in *)p->ai_addr;
            addr = &(sa->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6 *sa = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(sa->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("%s %s\n", ipver, ipstr);
    }

}

