#include "nethelper.h"
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#define BUFFERSIZE 65536

int main(int argc, char **argv) {
    int yes = 1;
    struct addrinfo servinfo;

    servinfo.ai_family = PF_PACKET;
    servinfo.ai_socktype = SOCK_RAW;
    servinfo.ai_protocol = htons(ETH_P_ALL);

    int fd = socket(servinfo.ai_family, servinfo.ai_socktype, servinfo.ai_protocol);
    handleerr(fd);

    char buffer[BUFFERSIZE];

    struct sockaddr caddr;
    socklen_t clen = sizeof caddr;

    int plen = recvfrom(fd, buffer, BUFFERSIZE, 0, &caddr, &clen);

    printf("Val is of len %d and = %s\n", plen, buffer);

    int c = 0;
    //http://stackoverflow.com/a/15860518/10996
    //The preamble is not part of the data read into the buffer.
    printf("Dest Address: %02x:%02x:%02x:%02x:%02x:%02x\n",buffer[c], buffer[c+1], buffer[c+2], buffer[c+3], buffer[c+4], buffer[c+5]);
    printf("Source Address: %02x:%02x:%02x:%02x:%02x:%02x\n",buffer[c+6], buffer[c+7], buffer[c+8], buffer[c+9], buffer[c+10], buffer[c+11]);

    int frame_type = buffer[c+12];
    if(frame_type == ETHERTYPE_IP) {
        printf("Frame type is IP\n");
    }
    printf("Frame type: %02x:%02x\n",buffer[c+12], buffer[c+13]);
    //freeaddrinfo(&servinfo);

    close(fd);

    return 0;
}

