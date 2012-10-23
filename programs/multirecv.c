#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  int s;
  struct sockaddr_in bindAddr;
  struct sockaddr_in him;
  struct ip_mreq mreq;
  int alen = sizeof(struct sockaddr_in);
  int Zero = 0;
  char msg[20];
  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    printf("couldn't get socket: %s\n", strerror(errno));
    return -1;
  };
  bindAddr.sin_family = AF_INET;
  bindAddr.sin_port = htons(5432);
  bindAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *)&bindAddr, sizeof(bindAddr)) < 0)
  {
    printf("bind error: %s\n", strerror(errno));
    return -1;
  };
  mreq.imr_multiaddr.s_addr = inet_addr("224.0.1.1");
  mreq.imr_interface.s_addr = INADDR_ANY;
  // multicast to self, enabled by default
  if (setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP, &Zero,sizeof(Zero))<0)
  {
    // not especially fatal
    printf("couldn't set multicast loopback: %s\n", strerror(errno));
  };
  // multicast to 224.0.1.1
  if (setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP, &mreq,sizeof(mreq))<0)
  {
    printf("couldn't set multicast membership: %s\n", strerror(errno));
    return -1;
  };
  // Receive reply, (could be from loopback)
  if (recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&him, &alen) < 0)
  {
    printf("recvfrom error: %s\n", strerror(errno));
    return -1;
  };
  printf("recieve from %s (%d)\n",inet_ntoa(him.sin_addr),
    ntohs((ushort)him.sin_port));
  return 0;
};
