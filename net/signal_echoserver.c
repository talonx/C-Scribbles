#include "mynet.h"

void echo(int connfd);
void handler(int signum);

void handler(int signum) {
	printf("Caught :%d\n", signum);//Not recommended, just testing.
}

void echo(int connfd) {
	ssize_t n;
	char buff[MAXLINE];
	again:
		while((n = read(connfd, buff, MAXLINE)) > 0) {
			writen(connfd, buff, n);
		}
		if(n < 0) {
			if(errno = EINTR) {
				goto again;
			} else {
				err_sys("read error");
			}
		}
}


int main(int argc, char **argv) {
	register_signal_handler(SIGALRM, handler);
    startserver(echo, 1025);
}

