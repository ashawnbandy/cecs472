#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// INADDR_ANY_INIT and in6addr_any are declared in netinet/in.h.
int main()
{
   int s, fd;
   int on = 1;
   struct sockaddr_in6 sin6;
   sin6.sin6_family = AF_INET6;
   sin6.sin6_flowinfo = 0;
   sin6.sin6_port = htons(23);
   sin6.sin6_addr = in6addr_any;

   if (bind(s, (struct sockaddr *) &sin6, sizeof(sin6)) == -1)
   {
    printf("failed\n");
   }
// loopback
   sin6.sin6_family = AF_INET6;
   sin6.sin6_flowinfo = 0;
   sin6.sin6_port = htons(23);
   sin6.sin6_addr = in6addr_loopback; // defined in netinet.in.h
   
  fd = socket(AF_INET6, SOCK_RAW, IPPROTO_IPV6);
  fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_ICMPV6);
  setsockopt(fd, IPPROTO_IPV6, IPV6_HOPLIMIT, &on, sizeof(on));
  return 0;
};
