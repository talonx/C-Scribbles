#include "../mynet.h"

#define URI 0
#define HOST 1

char *read_uri(char *buff);
char *read_host(char *buff);
void serve(int connfd);

void serve(int connfd) {
	ssize_t n;
	char buff[MAXLINE];
	int state = -1;
	char *uri;
	char *host;
	while((n = readline(connfd, buff, MAXLINE)) > 0) {
		//printf("%s", buff);
		if(n == 2) {
			if(buff[0] == '\r' && buff[1] == '\n') {
				printf("Reached end of req\n");
				break;
			}
		}
		switch(state) {
			case -1:
				uri = read_uri(buff);
				printf("URI:[%s]\n", uri);
				state = URI;
				break;
			case  0:
				host = read_host(buff);
				printf("Host:[%s]\n", host);
				state = HOST;
				break;
			case  1:
				printf("Read header: %s", buff);
				break;
			default:
				handleerr_s("Unknown state in request handler");
		}
		//writen(connfd, buff, n);
		//printf("Read %d\n", n);
	}
	//TODO handle n < 0
}

char *read_uri(char *buff) {
}


char *read_host(char *buff) {
}

int main(int argc, char **argv) {
    startserver(serve, 8181);
}

