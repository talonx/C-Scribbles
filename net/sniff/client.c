#include "nethelper.h"
#include <netdb.h>

void printit(struct addrinfo *);

int main(int argc, char **argv) {

    int yes = 1;

    int res;
    const char* node  = argv[1];
    //const char* service = NULL;
    struct addrinfo hints;
    struct addrinfo *servinfo;

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

    int cres = connect(fd, servinfo->ai_addr, servinfo->ai_addrlen);
    handleerr(cres);

    char buf[100];

    int bytes_recv = recv(fd, buf, 100, 0);
    handleerr(bytes_recv);

    printf("%s\n", buf);

    close(fd);

    freeaddrinfo(servinfo);

    return 0;
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

