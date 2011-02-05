#include "httpd.h"

char *rootdir;

void serve(int connfd) {
	printf("Rootdir is%s\n", rootdir);
	ssize_t n;
	char buff[MAXLINE];
	int state = -1;
	char *uri = malloc(100);
	char *host = malloc(100);
	while((n = readline(connfd, buff, MAXLINE)) > 0) {
		//printf("%s", buff);
		if(n == 2 && buff[0] == '\r' && buff[1] == '\n') {
			printf("Reached end of req\n");
			break;
		} else {
			switch(state) {
				case -1:
					read_uri(buff, uri);
					printf("URI:[%s]\n", uri);
					state = URI;
					break;
				case  0:
					read_host(buff, host);
					printf("Host:[%s]\n", host);
					state = HOST;
					break;
				case  1:
					printf("Read header: %s", buff);
					break;
				default:
					handleerr_s("Unknown state in request handler");
			}
		}
		//writen(connfd, buff, n);
		//printf("Read %d\n", n);
	}
    printf("Will serve the file \n");	
	writefile(uri, connfd);
	//TODO handle n < 0
	free(uri);
	free(host);
}

//GET / HTTP/1.1 \n
char *read_uri(char *buff, char *uri) {
    int m = indexof(buff, "GET");
	if(m == -1) {
		send_error("Only GET is supported", 501);//Check
		return;
	}
	int n, i = 0;
	for (n = m + 4; buff[n] != '\0' && buff[n] != ' '; n++) {
		uri[i++] = buff[n];
		//printf("uri char: %s\n", uri);
	}
	uri[i++] = '\0';
	printf("Returning uri %s\n", uri);
	return uri;
}

//Returns the first index of s2 in s1, else -1
int indexof(char *s1, char *s2) {
	int i, j, k;
	for (i = 0; s1[i] != '\0'; i++) {
		for (j = i, k = 0; s1[j] == s2[k] && s2[k] != '\0'; j++, k++) {
		}
		if(k > 0 && s2[k] == '\0') {
			return i;
		}
	}
	return -1;	
}

char *read_host(char *buff, char *host) {
}

void send_error(char *mes, int code) {
}

void writefile(char *uri, int connfd) {
	char fullpath[MAXLINE];
	strcat(fullpath, rootdir);
	strcat(fullpath,  uri);
	printf("Fullpath %s\n", fullpath);
	FILE *fp = fopen(fullpath, "r");
	if(fp == NULL) { //TODO handle specific errors
		printf("Error in opening file %s\n", fullpath);
	}

	writeresponseheader("HTTP/1.0 200 OK\r\n", connfd);//Not a header, the start line, but we're reusing the method
	writen(connfd, "\r\n", 2);

	int tot = 0;
	const char buff[BUFSIZE];
	int ret = fread(buff, sizeof(char), BUFSIZE, fp);
	tot += ret;
	while(ret > 0) {
		writen(connfd, buff, ret);
		ret = fread(buff, sizeof(char), BUFSIZE, fp);
		tot += ret;
//		printf("ret : %d\n", ret);
//		printf(buff);
	}

	writen(connfd, "\r\n", 2);
	printf("Wrote %d bytes\n", tot);
	fclose(fp);
}

/**void strcat(char *s1, char *s2) {
    while (*s1 != '\0') {
    	s1++;
    }
    while (*s1++ = *s2++);
}*/

void writeresponseheader(char *header, int connfd) {
	int size = strlen(header);
	writen(connfd, header, size);
}

int main(int argc, char **argv) {
    if (argc != 3) {
		printf("Usage: ./httpd <port> <root_dir>\n");
		exit(1);
	}
	int port = atoi(argv[1]);
	rootdir = argv[2];
	printf("Port is %d\n", port);
	printf("root dir %s\n", rootdir);
    startserver(serve, port);
}

