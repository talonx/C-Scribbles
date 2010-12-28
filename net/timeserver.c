#include "mynet.h"
#include <time.h>

int main(int argc, char **argv) {
	pid_t pid;
	int listenfd;
	int connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	handleerr(listenfd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(1025);
	
	int bres = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	handleerr(bres);
	int lres = listen(listenfd, MAXQLEN);
	handleerr(lres);

	for(;;) {
		len = sizeof(cliaddr);
		printf("Listening...\n");
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		handleerr(connfd);
		if((pid = fork()) == 0) {//child proc
			close(listenfd);
			printf("Connection from %s, port %d\n", inet_ntop(AF_INET, &(cliaddr.sin_addr), buff, sizeof(buff)), ntohs(cliaddr.sin_port));
			int f = sockfd_to_family(connfd);
			printf("Local family: %d\n", f);
			ticks = time(NULL);
			snprintf(buff, sizeof buff, "%.24s\r\n", ctime(&ticks));
			write(connfd, buff, strlen(buff));
			close(connfd);
			exit(0);
		}
		close(connfd);
	}
	
}

