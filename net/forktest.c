#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
main (int argc, char **argv)
{
        pid_t cpid;
        if (0==(cpid=fork())) {
                printf("child, pid %d\n",getpid());
                _exit(0);
        } else if (cpid > 0) {
                printf("parent, pid %d, child pid %d\n",getpid(),cpid);
        } else { /* cpid < 0 */
                printf("Fork failed, code %d, error: %s\n",
                       errno,strerror(errno));
        }
        exit(0);

}

