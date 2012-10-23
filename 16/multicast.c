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
  struct sockaddr_in bindAddr;
  struct sockaddr_in him;
  struct sockaddr_in multiAddr;
  struct in_addr inAnyAddr;
  struct in_addr interfaceToUse;
  struct ip_mreq mreq;
  int alen = sizeof(struct sockaddr_in);
  int One = 1;
  int Zero = 0;
  int result;
  int ttl;
  int oplen;
  char msg[20];
  char hostname[64];
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
  //if (setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP, &One,sizeof(One))<0)
  {
    printf("couldn't set multicast loopback: %s\n", strerror(errno));
    // not particularly fatal
  };
  // multicast to 224.0.1.1
  if (setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP, &mreq,sizeof(mreq))<0)
  {
    printf("couldn't set multicast membership: %s\n", strerror(errno));
    return -1;
  };
  // Multicast TTL defaults to 1
  // To get through gateways
  // ttl = 32;
  // oplen = sizeof(ttl);
  //result = getsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL, &ttl,&oplen);
  // If you need to override using the default interface.
  // oplen = sizeof(interfaceToUse);
  //result = setsockopt(s,IPPROTO_IP,IP_MULTICAST_IF, &interfaceToUse,&oplen);
  // Value to send
  strcpy(msg,"hi there");
  // Multicast to send to.
  multiAddr.sin_family = AF_INET;
  multiAddr.sin_port = htons(5432);
  multiAddr.sin_addr.s_addr = inet_addr("224.0.1.1");
  // Send
  if ( sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&multiAddr,
    sizeof(multiAddr)) < 0)
  {
    printf("sendto error: %s\n", strerror(errno));
    return -1;
  };
  // Receive reply, (could be from loopback)
  if (recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&him, &alen) < 0)
  {
    printf("sendto error: %s\n", strerror(errno));
    return -1;
  };
  // Other program should probably "recvfrom" then "sendto"
  return 0;
};
