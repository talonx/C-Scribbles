#include <stdio.h>

int inet_pton_loose(int family, const char* strptr, void* addrptr);

int inet_pton_loose(int family, const char* strptr, void* addrptr) {
    switch family {
        case AF_INET: 
            int res = inet_pton(family, strptr, addrptr);
            if(res == 0) { //invalid format
                res = inet_aton(strptr, addrptr);
                if(res == 0) {
                    return -1;
                }
		return res;
            }
	    return res;
        case AF_INET6:
	    
    }
}

int main(int argc, char **argv) {
    
}

