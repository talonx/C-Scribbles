#include "../mynet.h"

void serve(int connfd);

void serve(int connfd) {
	ssize_t n;
	char buff[MAXLINE];
	while((n = readline(connfd, buff, MAXLINE)) > 0) {
		printf("%s", buff);
		//writen(connfd, buff, n);
		//printf("Read %d\n", n);
		if(n == 2) {
			if(buff[0] == '\r' && buff[1] == '\n') {
				printf("Reached end of req\n");
				break;
			}
		}
	}
	//TODO handle n < 0
}


int main(int argc, char **argv) {
    startserver(serve, 8181);
}

