#include <unistd.h>
#include "mynet.h"

void handler(int);

int main(int argc, char **argv) {
    //signal(SIGALRM, handler);
    //struct sigaction act, oact;
	//act.sa_handler = handler;
    register_signal_handler(SIGALRM, handler);
	printf("Sleeping...\n");
	usleep(1000000000);
}


void handler(int signum) {
	printf("Caught %d\n", signum);
}
