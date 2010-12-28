#include "mynet.h"

void client(FILE *fp, int d);

void client(FILE *fp, int d) {
	char sendline[MAXLINE], recvline[MAXLINE];

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		writen(d, sendline, strlen(sendline));
		if(readline(d, recvline, MAXLINE) == 0) {
			printf("server terminated prematurely\n");
			exit(1);
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv) {
    int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2) {
		printf("Usage: client <ip address>\n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	handleerr(sockfd);
	bzero(&servaddr, sizeof servaddr);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1025);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	int cres = connect(sockfd, (struct sockaddr *) &servaddr, sizeof servaddr);
	client(stdin, sockfd);
	exit(0);
}

