/*
 * A. Shawn Bandy  
 * CECS472
 * Assignment 5 - UDP daytime client
 * 09/10/2012
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int     UDPdaytime(const char *host, const char *service);
#include "connectUDP.c"
/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectUDP(const char *host, const char *service);
 */

#define LINELEN         128
#define MSG		"Another walk about after dark/ It's my point of view...\n"
/*------------------------------------------------------------------------
 * main - UDP client for daytime service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *host = "panther";
        char    *service = "daytime";

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
                fprintf(stderr, "usage: UDPecho [host [port]]\n");
                exit(1);
        }
        UDPdaytime(host, service);
        exit(0);
}

/*------------------------------------------------------------------------
 * UDPecho - send input to daytime service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
UDPdaytime(const char *host, const char *service)
{
	char now[1024] = "\0";
	int s, n;

	s = connectUDP(host, service);

	(void) write(s, MSG, strlen(MSG));
	
	n = read(s, now, 1024);
	if(n > 0) {
		printf("(C) %s",now);
	} else {
		errexit("ERROR:  Network read failed.");
	}
/*
	char    buf[LINELEN+1];         /* buffer for one line of text  
        int     s, nchars;              /* socket descriptor, read count

        s = connectUDP(host, service);

        while (fgets(buf, sizeof(buf), stdin)) {
                buf[LINELEN] = '\0';    /* insure null-terminated 
                nchars = strlen(buf);
                (void) write(s, buf, nchars);

                if (read(s, buf, nchars) < 0)
                        errexit("socket read failed: %s\n",
                                        strerror(errno));
                fputs(buf, stdout);
        }
*/
}
