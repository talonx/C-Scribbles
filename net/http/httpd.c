#include "../mynet.h"

void serve(int connfd);

void serve(int connfd) {
	ssize_t n;
	char buff[MAXLINE];
	while((n = read(connfd, buff, MAXLINE)) > 0) {
		
		writen(connfd, buff, n);
	}
	//TODO handle n < 0
}


int main(int argc, char **argv) {
    startserver(serve, 8181);
}

