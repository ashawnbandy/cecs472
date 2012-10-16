/*
 * A. Shawn Bandy F1
 * CECS 472
 * Assignment 12 - Chat Client
 * 10/10/2012
 */


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/socket.h>
int     TCPecho(const char *host, const char *service);
#include "connectTCP.c"
#include "get_port.c"

/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectTCP(const char *host, const char *service);
 */
#define LINELEN         128
#define BUFSIZE		4096
int main(int argc, char *argv[])
{
        char    *host = "localhost";    /* host to use if none supplied */
        char    *service = get_port();      /* default service name         */
	struct timeval timeout;
	int ssock;
	fd_set rfds;
	fd_set afds;
	int nfds;
	int cc;

        switch (argc) {
        case 1:
                break;
        case 3:
                service = argv[2];
                /* FALL THROUGH */
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: TCPecho [host [port]]\n");
                exit(1);
        }
        signal(SIGPIPE, SIG_IGN);

	ssock = connectTCP(host,service);
        nfds = getdtablesize();
        
	FD_ZERO(&afds);
        FD_SET(0, &afds);
	FD_SET(ssock,&afds);


        while(1) {
		char buf[BUFSIZE] = {};
 		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
 		memcpy(&rfds, &afds, sizeof(rfds));

                if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
                                &timeout) < 0)
                        errexit("select: %s\n", strerror(errno));
		if(timeout.tv_sec == 0 && timeout.tv_usec ==0 ) {
			printf("Are you there?\n");
		} else {
			if(FD_ISSET(0,&rfds)) { 
				if(fgets(buf,sizeof(buf),stdin) != NULL) {
					send(ssock,buf,strlen(buf),0);
				} else {
					FD_CLR(0,&afds);
					(void) close(0);
					shutdown(ssock,SHUT_WR);
				}
			}
			if(FD_ISSET(ssock,&rfds)) {
				cc = recv(ssock,buf,sizeof(buf),0);
				if(cc <= 0) {
					FD_CLR(ssock,&afds);
					(void) close(ssock);
					exit(0);
				} else {
					printf("%s",buf);
				}
			}
		}
	}				
 	exit(0);	
}
