
/* A. Shawn Bandy F1
 * CECS 472
 * Homework 13 - multiprotocol server
 * 10/15/2012
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void	timeofday(char buf[]);
#include "passiveTCP.c"
#include "passiveUDP.c"
//int	errexit(const char *format, ...);
//int	passiveTCP(const char *service, int qlen);
//int	passiveUDP(const char *service);

#include "get_port.c"

#define	MAX(x, y)	((x) > (y) ? (x) : (y))

#define	QLEN		  5

#define	LINELEN		128

int
main(int argc, char *argv[])
{
	char	*service = get_port();	/* service name or port number	*/
	char	buf[8];		/* buffer for one line of text	*/
	struct sockaddr_in fsin;	/* the request from address	*/
	int	alen;			/* from-address length		*/
	int	tsock; 			/* TCP master socket		*/
	int	usock;			/* UDP socket			*/
	int	nfds;
	fd_set	rfds;			/* readable file descriptors	*/

	switch (argc) {
	case	1:
		break;
	case	2:
		service = argv[1];
		break;
	default:
		errexit("usage: daytimed [port]\n");
	}

	tsock = passiveTCP(service, QLEN);
	usock = passiveUDP(service);
	nfds = MAX(tsock, usock) + 1;	/* bit number of max fd	*/

	FD_ZERO(&rfds);

	while (1) {
		FD_SET(tsock, &rfds);
		FD_SET(usock, &rfds);

		if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
				(struct timeval *)0) < 0)
			errexit("select error: %s\n", strerror(errno));
		if (FD_ISSET(tsock, &rfds)) {
			int	ssock;		/* TCP slave socket	*/

			alen = sizeof(fsin);
			ssock = accept(tsock, (struct sockaddr *)&fsin,
				&alen);
			if (ssock < 0)
				errexit("accept failed: %s\n",
						strerror(errno));
			timeofday(buf);
			(void) write(ssock, buf, 8);
			(void) close(ssock);
		}
		if (FD_ISSET(usock, &rfds)) {
			alen = sizeof(fsin);
			if (recvfrom(usock, buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, &alen) < 0)
				errexit("recvfrom: %s\n",
					strerror(errno));
			timeofday(buf);
			(void) sendto(usock, buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, sizeof(fsin));
		}
	}
}

void timeofday(char buf[]) {
	struct timeval now;
        (void) gettimeofday(&now,NULL);
	printf("%x %x\n",now.tv_sec,now.tv_usec);
	now.tv_sec = htonl(now.tv_sec);
	now.tv_usec = htonl(now.tv_usec);
	printf("%i\n",sizeof(now.tv_sec));
	memcpy(&buf[0],&now.tv_sec,4);
	printf("%i\n",sizeof(now.tv_usec));
	memcpy(&buf[4],&now.tv_usec,4);
	printf("%i\n",sizeof(buf));
}
