/*
 *  client.c:
 *      Requests a socket connection to the address at which the server 
 *      listens. Writes a message the server via the socket.
 *      Reads the server's reply from the same socket.
 *      Closes the socket.
 *
 * The format of the command is
 *      client nameofserver
 * If no server is named, the name defaults to aardvark.cecs.csulb.edu
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "print_socket.c"
#include "print_remote.c"

/* ************************************************************* */
/* Get a connection to a well-known socket on a remote machine.
 * This function returns the socket discriptor for that connection
 * If there is an error a negative number is returned:
 *   -1 indicates we couldn't build a socket
 *   -2 indicates we couldn't make the connection to the remote machine
 * If compiled as cc -DDEBUG client.c then the debugging stuff will be
 * printed so we can connections are made.
 */
int get_connection(server_name)
char *server_name;
{
  int my_socket;
  struct sockaddr_in      his_address;
  struct hostent *hp;
  u_short well_known_port = htons(6000 + getuid());
  unsigned long inet_address;
  /* Get a socket. */
  my_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (my_socket < 0) {
    perror("client: couldn\'t build socket\n");
    return -1;
  }
  /* Set up the socket structure */
  /* Get the correct address for the machine. */
  hp = gethostbyname(server_name);
  if (hp == NULL) perror("client: Can't get host name\n");
  /* Put the address into the socket structure */
  bzero ((char *) &his_address, sizeof(his_address));
  bcopy(hp->h_addr, (char *)&his_address.sin_addr, hp->h_length);
  /* h_addrtype is 2 (AF_INET) */
  /* Set socket structure for internet protocol. */
  his_address.sin_family = AF_INET;  /* AF_INET is 2 (sys/socket.h) */
  /* Aim at the well known port. */
  his_address.sin_port = well_known_port;
  /* Request the connection to the server */
#ifdef DEBUG
  printf("client: attempting connect to ");
  printf("%s, ",inet_ntoa(his_address.sin_addr));
  printf("port %d\n",ntohs(his_address.sin_port));
#endif
  if (connect(my_socket, (struct sockaddr *) &his_address, 
      sizeof(his_address)) < 0) {
    perror("client: error on connect\n");
    return -2;
  }
#ifdef DEBUG
  printf("client: connected using descriptor %d.\n", my_socket);
  print_remote(my_socket);
#endif
  return my_socket;
}

/* ************************************************************* */
int main(argc, argv)
int argc;
char *argv[];
{
  int server_connection;
  char message[80];
  strcpy(message,"Client speaks" );
  if (argc == 2)
    server_connection = get_connection(argv[1]);
  else
    server_connection = get_connection("aardvark.cecs.csulb.edu");
  print_socket(server_connection);
    /*Send a message to server*/
  write(server_connection, message, 80);
    /*Get server's reply*/
  read(server_connection, message, 80);
    /*Print the servers reply */
  printf(">> %s\n",message);
    /*Shut down our end of the socket to free the channel*/
  close(server_connection);
  return 0;
}
