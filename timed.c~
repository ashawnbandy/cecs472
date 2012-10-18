/* 
 * A. Shawn Bandy
 * CECS 472
 * Assignment 7 - Server
 * 09/18/2012
 *
 * timed.c - main */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "passiveUDP.c"
#include "get_port.c"

/* handled by the include
 * int     passiveUDP(const char *service);
 * int     errexit(const char *format, ...);
 */

#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */

int
main(int argc, char *argv[])
{
        struct sockaddr_in fsin;        /* the from address of a client */
        char    *service = get_port();      /* service name or port number  */
        char    buf[1];                 /* "input" buffer; any size > 0 */
        int     sock;                   /* server socket                */
        struct timeval  now;                    /* current time                 */
        int     alen;                   /* from-address length          */
	char 	out_buf[8];

        switch (argc) {
        case    1:
                break;
        case    2:
                service = argv[1];
                break;
        default:
                errexit("usage: UDPtimed [port]\n");
        }

        sock = passiveUDP(service);
	
	printf("Server listening on:  %s\n",get_port());

        while (1) {
                alen = sizeof(fsin);
                if (recvfrom(sock, buf, sizeof(buf), 0,
                                (struct sockaddr *)&fsin, &alen) < 0)
                        errexit("recvfrom: %s\n", strerror(errno));
                (void) gettimeofday(&now,NULL);
		printf("%x %x\n",now.tv_sec,now.tv_usec);
		
		now.tv_sec = htonl(now.tv_sec);
		now.tv_usec = htonl(now.tv_usec);
		memcpy(&out_buf,&now.tv_sec,4);
		memcpy(&out_buf[4],&now.tv_usec,4);
		(void) sendto(sock, &out_buf, sizeof(out_buf),0,(struct sockaddr*)&fsin,sizeof(fsin));
		
	}
}
