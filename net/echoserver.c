#include "mynet.h"

void echo(int connfd);

void echo(int connfd) {
	ssize_t n;
	char buff[MAXLINE];
	again:
		while((n = read(connfd, buff, MAXLINE)) > 0) {
			writen(connfd, buff, n);
		}
		if(n < 0) {
			if(errno == EINTR) {
				goto again;
			} else {
				handleerr_s("read error");
			}
		}
}


int main(int argc, char **argv) {
    startserver(echo, 1025);
}

