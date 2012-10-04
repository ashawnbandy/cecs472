/*
 * A. Shawn Bandy
 * CECS 472
 * Assignment 8 - Client
 * 09/10/2012
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>

#include "connectTCP.c" //provides int connectTCP(host, service)
#include "get_port.c"

#define UNIXEPOCH 2208988800UL
#define MSG "Another walk about after dark/ It's my point of view\n"

int main(int argc, char *argv[]) {
	char	*host = "localhost";
	char	*service = get_port();
	int 	s,n;
	struct timeval now;
	
	char buf[8];
	int inchars;

	switch(argc) {
		case 1: 
			break;
		case 3: 
			service = argv[2];
			//fall through
		case 2:
			host = argv[1];
			break;
		default:
			errexit("ERROR: Too many commmand line options.");
	}
	
	s = connectTCP(host,service);
	for(inchars=0;inchars<sizeof(buf);inchars+=n) {
		n=read(s,&buf[inchars],sizeof(buf)-inchars);
		if(n <= 0) errexit("ERROR: network read failed");
	}
	memcpy(&now.tv_sec,&buf,4);
	memcpy(&now.tv_usec,&buf[4],4);
	printf("%x %x\n",ntohl(now.tv_sec),ntohl(now.tv_usec));
	exit(0);
}

