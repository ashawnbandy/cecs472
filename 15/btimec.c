
/*
 * A. Shawn Bandy F1
 * CECS 472
 * Assignment 15 - Broadcast gtod Client
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
#include "connectUDP.c"
#include "get_port.c"

/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectTCP(const char *host, const char *service);
 */
#define LINELEN         128
#define BUFSIZE		4096
int main(int argc, char *argv[])
{
        // char    *host = "localhost";    /* host to use if none supplied */
        char    *service = get_port();      /* default service name         */
	struct timeval now;
	int ssock;
	int alen = sizeof(struct sockaddr_in);
	struct sockaddr_in fsin, fsin_him;
	int One = 1;
	
	fd_set rfds;
	fd_set afds;
	int nfds;
	int cc;
	/*
        switch (argc) {
        case 1:
                break;
        case 3:
                service = argv[2];
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: <?> [host [port]]\n");
                exit(1);
        }
	*/

        signal(SIGPIPE, SIG_IGN);

	ssock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//ssock = connectUDP(host,service);
  
	/* enabling broadcast */

	setsockopt(ssock,SOL_SOCKET,SO_BROADCAST,&One,sizeof(One));

	fsin.sin_family = AF_INET;
	fsin.sin_port = htons(atoi(service));
	fsin.sin_addr.s_addr = INADDR_BROADCAST;

	nfds = getdtablesize();
        
	FD_ZERO(&afds);
        FD_SET(0, &afds);
	FD_SET(ssock,&afds);


        while(1) {
		char buf[BUFSIZE] = {};
 		memcpy(&rfds, &afds, sizeof(rfds));

                if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
                                (struct timeval *)0) < 0)
                        errexit("select: %s\n", strerror(errno));
		
			if(FD_ISSET(0,&rfds)) { 
				switch(getchar()) {
					case 'n':
						sendto(ssock," ",1,0,(struct sockaddr *)&fsin,sizeof(fsin));
						break;
					case 'q':
						FD_CLR(0,&afds);
						(void) close(0);
						exit(0);
					}
			}
			
			if(FD_ISSET(ssock,&rfds)) {
				cc = recvfrom(ssock, buf, sizeof(buf), 0,
					(struct sockaddr *)&fsin, &alen);
        			if (cc <= 0) {
					FD_CLR(ssock,&afds);
					(void) close(ssock);
					exit(0);
				} else {
        				memcpy(&now.tv_sec,&buf,4);
					memcpy(&now.tv_usec,&buf[4],4);
					now.tv_sec = htonl(now.tv_sec);
					now.tv_usec = htonl(now.tv_usec);
					printf("%x %x\n",now.tv_sec,now.tv_usec);
				}
				/*
				cc = recv(ssock,buf,sizeof(buf),0);
				if(cc <= 0) {
					FD_CLR(ssock,&afds);
					(void) close(ssock);
					exit(0);
				} else {
					write(0,buf,cc);
				}
				*/
			}
	}
}			

