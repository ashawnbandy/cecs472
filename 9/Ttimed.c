/* 
 * A. Shawn Bandy
 * CECS 472
 * Assignment 8 
 * Ttimed.c - Server */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int             TCPdaytimed(int fd);
#include "passiveTCP.c"
#include "get_port.c"

/* handled by the include
 * int             errexit(const char *format, ...);
 * int             passiveTCP(const char *service, int qlen);
 */

#define QLEN    5

int
main(int argc, char *argv[])
{
        struct  sockaddr_in fsin;       /* the from address of a client */
        char    *service = get_port();   /* service name or port number  */
        int     msock, ssock;           /* master & slave sockets       */
        int     alen;                   /* from-address length          */

        switch (argc) {
        case    1:
                break;
        case    2:
                service = argv[1];
                break;
        default:
                errexit("<klaxon>\n");
        }

        msock = passiveTCP(service, QLEN);

        while (1) {
                alen = sizeof(fsin);
                ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
                if (ssock < 0)
                        errexit("accept failed: %s\n", strerror(errno));
                (void) Ttimed(ssock);
                (void) close(ssock);
        }
}

int
Ttimed(int fd)
{
	char buf[8];
	struct timeval now;

	(void) gettimeofday(&now,NULL);
	printf("%x %x\n",now.tv_sec,now.tv_usec);
	now.tv_sec = htonl(now.tv_sec);
	now.tv_usec = htonl(now.tv_usec);
	memcpy(&buf,&now.tv_sec,4);
	memcpy(&buf[4],&now.tv_usec,4);
	(void) write(fd, buf, 8);
        return 0;
}
