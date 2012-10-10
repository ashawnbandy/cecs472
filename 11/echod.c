/*
 * A. Shawn Bandy F1
 * CECS472
 * Assignment 11 - Multi-Echo Chat Server
 * 10/08/2012
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define QLEN               5    /* maximum connection queue length      */
#define BUFSIZE         4096

#include "passiveTCP.c"
#include "get_port.c"
/* handled by the include
 * int             errexit(const char *format, ...);
 * int             passiveTCP(const char *service, int qlen);
 */
int             echo(int fd);

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *service = get_port();      /* service name or port number  */
        struct sockaddr_in fsin;        /* the from address of a client */
        int     msock;                  /* master server socket         */
        fd_set  rfds;                   /* read file descriptor set     */
        fd_set  afds;                   /* active file descriptor set   */
        int     alen;                   /* from-address length          */
        int     fd, fd2,nfds;
 	char buf[BUFSIZ];
 	int cc;

        switch (argc) {
        case    1:
                break;
        case    2:
                service = argv[1];
                break;
        default:
                errexit("usage: TCPmechod [port]\n");
        }

	signal(SIGPIPE, SIG_IGN);

        msock = passiveTCP(service, QLEN);

        nfds = getdtablesize();
        FD_ZERO(&afds);
        FD_SET(msock, &afds);

        while (1) {
		buf[BUFSIZ] = {};
                memcpy(&rfds, &afds, sizeof(rfds));

                if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
                                (struct timeval *)0) < 0)
                        errexit("select: %s\n", strerror(errno));
                if (FD_ISSET(msock, &rfds)) {
                        int     ssock;

                        alen = sizeof(fsin);
                        ssock = accept(msock, (struct sockaddr *)&fsin,
                                &alen);
                        if (ssock < 0)
                                errexit("accept: %s\n",
                                        strerror(errno));
                        FD_SET(ssock, &afds);
                }
                for (fd=0; fd<nfds; ++fd) {
                        if (fd != msock && FD_ISSET(fd, &rfds)) {
				cc = recv(fd, buf, sizeof buf, 0);
				if (cc <= 0) {
					FD_CLR(fd,&afds);
					(void) close(fd);
				} else {
					printf("\n%i (%i): %s",fd,nfds,buf);
					for (fd2 = 0; fd2 < nfds; ++fd2) {
						if(fd2 != fd && fd2 != msock) {
							printf("%i ",fd2);
							if(send(fd2, buf, sizeof buf, 0) <= 0) {
								FD_CLR(fd2,&afds);
								(void) close(fd2);
							}
						}
					}	
				}
			}
		}
		printf("***\n");
	}
}
