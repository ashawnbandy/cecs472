/*
 * A. Shawn Bandy
 * CECS 472
 * Assignment 6
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

#define UNIXEPOCH 2208988800UL
#define MSG "Another walk about after dark/ It's my point of view\n"

int main(int argc, char *argv[]) {
	char	*host = "panther";
	char	*service = "time";
	int 	s,n;
	time_t now;
	
	char buf[4];
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
	for(inchars=0;inchars<4;inchars+=n) {
		n=read(s,&buf[inchars],4-inchars);
		if(n <= 0) errexit("ERROR: network read failed");
	}
	memcpy(&now,buf,4);
	now = ntohl(now);
	now -= UNIXEPOCH;
	printf("%s",ctime(&now));
	exit(0);
}

