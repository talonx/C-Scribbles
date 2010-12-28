#include "mynet.h"

void ttest();

int main(int argc, char **argv) {
	for (;;) {
		ttest();
	}
}

void ttest() {
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
        int size = sizeof(struct sockaddr_storage);
        int lres = connect(d, res->ai_addr, size);
        handleerr(lres);
        
        char mes[100];
        printf("%d\n", sizeof(mes));
        int rres = recv(d, mes, sizeof(mes), 0);
        handleerr(rres);
        if(rres == 0) {
            printf("0 bytes were read\n");
        } else {
            printf("Received : %s\n", mes);
            printf("%d\n", rres);
        }
        close(d);
    }
}
