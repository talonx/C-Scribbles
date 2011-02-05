#include "../mynet.h"
#define URI 0
#define HOST 1
#define BUFSIZE 128

char *read_uri(char *buff, char *uri);
char *read_host(char *buff, char *uri);
int indexof(char *str, char *inner);
void serve(int connfd);
void send_error(char *mes, int code);
void writefile(char *uri, int connfd);
void writeresponseheader(char *header, int connfd);

