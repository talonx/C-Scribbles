#include "../mynet.h"

void serve(int connfd);

void int serve(int connfd) {
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
    startserver(serve);
}

