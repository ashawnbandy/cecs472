/*
 * A. Shawn Bandy
 * CECS 472
 * Assignment 4
 * 09/11/2012
*/
#include <sys/types.h> /* u_long */
#include <netdb.h> /* getXbyY */
#include <netinet/in.h> /*htons*/
#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
#include <arpa/inet.h> /*inet_ntoa*/
int main(int argc, char *argv[])
{
	struct hostent *hp;
	struct servent *sp, *sp2;
	struct in_addr addr;
	printf("--Info--\n");
	if(argc == 5) {
		//ARGUMENT 1
		hp = gethostbyname(argv[1]);
		if(hp) {
			memcpy(&addr, hp->h_addr, hp->h_length);
			printf("Hostname from %s:  %s\n",argv[1],inet_ntoa(addr));
		} else {
			printf("ERROR: gethostbyname failed on %s\n",argv[1]);
		}		
		
		//ARGUMENT 2
		sp = getservbyname(argv[2],"tcp");
		if(sp) {
			printf("Port number from service name %s: %i\n",argv[2],ntohs(sp->s_port));
		} else {
			printf("ERROR: getservicebyname failed on %s\n",argv[2]);
		}

		//ARGUMENT 3
		sp2 = getservbyport(htons(atoi(argv[3])),"tcp");
		if(sp2) {
			printf("Service name from port %s: %s\n",argv[3],sp2->s_name);
		} else {
			printf("ERROR: getservbyport failed on %s\n",argv[3]);
		}
		//ARGUMENT 4
		if(inet_addr(argv[4]) != INADDR_NONE) {
			printf("Internet address of %s: %i\n",argv[4],inet_addr(argv[4]));
		} else {
			printf("ERROR: inet_addr failed on %s\n",argv[4]);
		}
	} else {
		printf("ERROR: Wrong number of arguments.");
	}
	printf("--/Info--\n");
	/*
  struct hostent *hp, *hp2;
  struct in_addr addr;
  
  hp = gethostbyname("cheetah.cecs.csulb.edu");
  printf("%s\n",hp->h_name);
  printf("%d\n",hp->h_length);
  memcpy(&addr, hp->h_addr, hp->h_length);
  printf("%x\n",ntohl(addr.s_addr));
  printf("%s\n",inet_ntoa(addr));
  hp2 = gethostbyaddr(&addr, 4, AF_INET);
 
  {
  struct servent *sp, *sp2;
  sp = getservbyname("telnet", "tcp");
  printf("%s\n",sp->s_name); // telnet 
  printf("%d\n",ntohs(sp->s_port)); // 23 
  printf("%s\n",sp->s_proto); // tcp 
  sp2 = getservbyport(htons(23), "tcp");
  */
  
  return 0;
};

