/*
 * A. Shawn Bandy
 * CECS 472
 * Homework 16 - Multicast Sender
 * 10-22-2012
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "get_port.c"

int main(int argc, char* argv[])
{
  int s;
  struct sockaddr_in multiAddr;
  struct timeval now;
  char out_buf[8];

  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    printf("couldn't get socket: %s\n", strerror(errno));
    return -1;
  };
  // Multicast to send to.
  multiAddr.sin_family = AF_INET;
  multiAddr.sin_port = htons(atoi(get_port()));
  multiAddr.sin_addr.s_addr = inet_addr("224.0.1.1");
  	
	while(sleep(1) == 0) {
		(void) gettimeofday(&now,NULL);
		printf("(MS) %x %x\n",now.tv_sec,now.tv_usec);	
		now.tv_sec = htonl(now.tv_sec);
		now.tv_usec = htonl(now.tv_usec);
		memcpy(&out_buf[0],&now.tv_sec,4);
		memcpy(&out_buf[4],&now.tv_usec,4);
  	
		if ( sendto(s, &out_buf, 8, 0, (struct sockaddr *)&multiAddr, sizeof(multiAddr)) < 0) 
    			printf("sendto error: %s\n", strerror(errno));
  	
		
		
	}
}
