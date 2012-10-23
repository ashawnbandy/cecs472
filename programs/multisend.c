#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int s;
  struct sockaddr_in multiAddr;
  char* msg = "Hi There";
  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    printf("couldn't get socket: %s\n", strerror(errno));
    return -1;
  };
  // Multicast to send to.
  multiAddr.sin_family = AF_INET;
  multiAddr.sin_port = htons(5432);
  multiAddr.sin_addr.s_addr = inet_addr("224.0.1.1");
  // Send
  if ( sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&multiAddr,
    sizeof(multiAddr)) < 0)
  {
    printf("sendto error: %s\n", strerror(errno));
    return -1;
  };
  printf("sent multicast\n");
  return 0;
};
