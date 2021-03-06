/*
 * A. Shawn Bandy
 * CECS 472
 * Homework 16 - Multicast Receiver
 * 10/22/2012
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "get_port.c"

int main(int argc, char* argv[])
{
  int s;
  struct sockaddr_in bindAddr;
  struct sockaddr_in him;
  struct ip_mreq mreq;
  int alen = sizeof(struct sockaddr_in);
  int Zero = 0;
  char buf[8];
  struct timeval now;


  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    printf("couldn't get socket: %s\n", strerror(errno));
    return -1;
  };
  bindAddr.sin_family = AF_INET;
  bindAddr.sin_port = htons(atoi(get_port()));
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
  while (recvfrom(s, buf, 8, 0, (struct sockaddr *)&him, &alen) > 0)
  {
        memcpy(&now.tv_sec,&buf,4);
	memcpy(&now.tv_usec,&buf[4],4);
	now.tv_sec = htonl(now.tv_sec);
	now.tv_usec = htonl(now.tv_usec);
	printf("%x %x\n",now.tv_sec,now.tv_usec);
  }
  printf("recvfrom error: %s\n", strerror(errno));
  return -1;
}


