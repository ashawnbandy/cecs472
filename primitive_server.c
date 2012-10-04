//A. Shawn Bandy
//CECS 472
//ASSIGNMENT 3 - SERVER
//09/05/2012
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void rw(int s, void *message, size_t count);

int main(){
  int master, client, len; char message[80];
  struct sockaddr_in my_addr, his_addr;
  /* get a socket allocated */
  master = socket(PF_INET, SOCK_STREAM, 0);
  printf("\n--==Server==--\nMaster socket: %i\n",master);
  /* bind to the well-known port on our machine */
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = INADDR_ANY;
  my_addr.sin_port = htons(7654);
  printf("Bind returns: %i\n", bind(master, (struct sockaddr *) &my_addr, sizeof(my_addr)));
  printf("Listen returns: %i\n",listen(master, 5));
  len=sizeof(his_addr);
  /* get the connection to the client */
  client = accept(master, (struct sockaddr *) &his_addr, &len);
  printf("Client socket: %i\n", client);
    /* get the message from the client */
  strcpy(message,"Server replies");
  rw(client, message, 80); /* send reply */
  rw(client, message, 80);
  close(client);
  close(master);
  return 1;
}

void rw(int s, void *message, size_t count) {
	        char r_message[80];
		printf("(S)Read bytes: %i\n", read(s,r_message,count));
		printf("(S)Client sent: %s\n", r_message);
		printf("(S)Write bytes: %i\n", write(s,message,count));
		printf("(S)Server replies with: %s\n",message);
}
