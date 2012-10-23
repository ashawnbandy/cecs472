/* daytimed.c - main */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */

#include "passiveTCP.c"
#define  QLEN      5

int main(int argc, char *argv[])
{
  char  *service = "5001";  /* service name or port number  */
  char  buf[4];    /* buffer for one line of text  */
  struct sockaddr_in fsin;  /* the request from address  */
  int  alen;      /* from-address length    */
  int  tsock;       /* TCP master socket    */
  time_t  now;                    /* current time                 */
  int failcount = 0;

  switch (argc) {
  case  1:
    break;
  case  2:
    service = argv[1];
    break;
  default:
    errexit("usage: daytimed [port]\n");
  }

  tsock = passiveTCP(service, QLEN);

  while (1) {
      int  ssock;    /* TCP slave socket  */
      alen = sizeof(fsin);
      ssock = accept(tsock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0)
      {
        printf("accept failed: %s\n", strerror(errno));
        // Back around to the accept.
        continue;
      };
      // Get the time
      (void) time(&now);
      // Convert to protocol standard
      now = htonl((u_long)(now + UNIXEPOCH));
      // Into a buffer so we can send it in pieces.
      memcpy(buf,&now,4);
      (void) write(ssock, &buf[0], 1);
      sleep(1);
      (void) write(ssock, &buf[1], 2);
      sleep(1);
      failcount++;
      if (failcount>=5)
      {
        // A premature close will happen
        failcount = 0;
      }
      else
      {
        // Normal time completion
        (void) write(ssock, &buf[3], 1);
      }
      (void) close(ssock);
  }
}
