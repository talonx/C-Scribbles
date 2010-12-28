#include "net.h"


int main(int argc, char **argv) {
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, "1025", &hints, &res);
    if(status) {//error
        printf("Errored in getaddrinfo: %d\n", status);
    } else {
        int d = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        handleerr(d);
        int bres = bind(d, res->ai_addr, res->ai_addrlen);
        handleerr(bres);
        int lres = listen(d, 5);
        handleerr(lres);
        int size = sizeof(struct sockaddr_storage);
        for (;;) {
	        int ares = accept(d, res->ai_addr, &size);
                printf("Connection from %s, port %d\n", inet_ntop(res->ai_addr), res->ai_port);
	        handleerr(ares);
	        char *mes = "Hullo";
	        int mlen = strlen(mes);
	        printf("Message len %d\n", mlen);
	        int sres = send(ares, mes, mlen, 0);
	        handleerr(sres);
	        if(sres != mlen) {
	            printf("Not sent the whole mes: %d sent, but were %d\n", sres, mlen);
		}
        	close(ares);
	}
        close(d);
    }
}

