#include "../mynet.h"

#define URI 0
#define HOST 1
#define BUFSIZE 128

#define FOUR_O_FOUR_STARTLINE "HTTP/1.0 404 Not Found"
#define LENGTH_404_STARTLINE strlen(FOUR_O_FOUR_STARTLINE)

char *read_uri(char *buff, char *uri);
char *read_host(char *buff, char *uri);
int indexof(char *str, char *inner);
void serve(int connfd);
void send_error(int connfd, char *mes, int code);
void writefile(char *uri, int connfd);
void writeresponseheader(char *header, int connfd);

