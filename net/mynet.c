#include "mynet.h"

/**
 * This function's code is from Richard Stevens' UNP 3rd ed Vol 1
 */
ssize_t writen(int fd, const void *vptr, size_t n) {
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return (-1);
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}

/**
 * This function's code is from Richard Stevens' UNP 3rd ed Vol 1
 */
ssize_t readn(int fd, void *vptr, size_t n) {
	size_t nleft;
	ssize_t nread;
	char *ptr;
	ptr = vptr;
	nleft = n;
	while(nleft >= 0) {
		if((nread = read(fd, ptr, nleft)) < 0) {
			if(errno == EINTR) {
				nread = 0;
			} else {
				return -1;
			}
		} else if (nread == 0) {
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return n - nleft;
}

int sockfd_to_family(int sockfd) {
	struct sockaddr_storage ss;
	socklen_t len;
	len = sizeof ss;
	if(getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0) {
		return -1;
	}
	return ss.ss_family;
}

void handleerr_s(char *mes) {
    printerror_s(mes);
    exit(1);
}

void handleerr(int d) {
    if(d == -1) {
        printerror(errno);
        exit(1);
    }
}

void printerror(int err) {
    printf("Error is %d: %s\n", errno, strerror(errno));
}

void printerror_s(char *mes) {
    printf("Error is %s\n", mes);
}

/**
 * Starts a server process taking a pointer to a function. This function is invoked
 * in a forked process when a client connects.
 */
void startserver(void (*func)(int), int port) {
	pid_t pid;
	int listenfd;
	int connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	handleerr(listenfd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);
	
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
			func(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);
	}
	
}


/**
 * These 2 functions' code are from Richard Stevens' UNP 3rd ed Vol 1
 */
static int read_cnt;
static char read_buf[MAXLINE];
static char *read_ptr;
static ssize_t my_read(int fd, char *ptr) {
	if (read_cnt <= 0) {
		again:
			if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
				if (errno == EINTR)
					goto again;
				return (-1);
			} else if (read_cnt == 0)
				return (0);
			read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return (1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen) {
	ssize_t n, rc;
	char c, *ptr;
	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = my_read(fd, &c)) == 1) {
			*ptr++ = c; 
			if (c == '\n') 
				break; /* newline is stored, like fgets() */ 
		} else if (rc == 0) {
			*ptr = 0; 
			return (n - 1);
		} else
			return (-1);
	}
	*ptr = 0;
	return (n); 
}


/**
 * Register a Signal handler function for the specified signal
 */
void register_signal_handler(int signum, sigfunc * handler) {
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	int ret = sigaction(signum, &act, NULL);
	if(ret != 0) {
		printf("Failed to set signal handler for %d. Error code: %d\n", signum, ret);
		exit(1);
	}
}
