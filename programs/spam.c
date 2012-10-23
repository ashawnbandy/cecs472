/* TCPmechod.c - main, echo */

/* <<< indicates changes to TCPmechod.c */
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
#include "passiveUDP.c" /* <<< */
/* handled by the include
 * int             errexit(const char *format, ...);
 * int             passiveTCP(const char *service, int qlen);
 */
int             echo(int fd);

char ubuf[BUFSIZE]; /* <<< */

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
  char    *service = "echo";      /* service name or port number  */
  struct sockaddr_in fsin;        /* the from address of a client */
  int     msock;                  /* master server socket         */
  int     usock;                  /* UDP <<<  */ 
  fd_set  rfds;                   /* read file descriptor set     */
  fd_set  afds;                   /* active file descriptor set   */
  int     alen;                   /* from-address length          */
  int     fd, nfds;
  
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
  usock = passiveUDP(service); /* <<< */
  ubuf[0] = '\0'; /* no spam at start */ /* <<< */

  nfds = getdtablesize();
  FD_ZERO(&afds);
  FD_SET(msock, &afds);
  FD_SET(usock, &afds); /* <<< */

  while (1) {
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
    if (FD_ISSET(usock, &rfds)) { /* <<< the entire if */
      int n;
      alen = sizeof(fsin);
      n = recvfrom(usock, ubuf, sizeof(ubuf), 0,
        (struct sockaddr *)&fsin, &alen);
      if (n < 0) errexit("recvfrom: %s\n", strerror(errno));
      ubuf[n] = '\0';

    }
    for (fd=0; fd<nfds; ++fd)
      if (fd != msock && FD_ISSET(fd, &rfds) && fd != usock) /* <<< */
        if (echo(fd) == 0) {
                (void) close(fd);
                FD_CLR(fd, &afds);
        }
  }
}

/*------------------------------------------------------------------------
 * echo - echo one buffer of data, returning byte count
 *------------------------------------------------------------------------
 */
int
echo(int fd)
{
  char    buf[BUFSIZ];
  int     cc;

  cc = recv(fd, buf, sizeof buf, 0);
  if (cc < 0)
          errexit("echo read: %s\n", strerror(errno));
  if (cc && (send(fd,ubuf,strlen(ubuf),0) < 0) &&  /* <<< */
     	(send(fd, buf, cc, 0) < 0))
          errexit("echo write: %s\n", strerror(errno));
  return cc;
}
