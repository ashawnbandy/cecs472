/* server.c:
 *  The server end of the communications link. It listens at `well-known' port 
 *  address. When a request (connect) arrives it reads the message and prints 
 *  it. It then sends a reply. The connection is then closed.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include "print_socket.c"
#include "print_remote.c"

/* ************************************************************* */
/* Get a master socket for the server. This function returns the socket 
 * descriptor if the socket was successfully opened, otherwise it returns a
 * negative number indicating an error. This function should be called only
 * once during the running of the program. Since the listen also only
 * needs to be done once during the running of the program, we do it just
 * before we return.
 *    -1 probably indicates no more discriptors are available (socket failed)
 *    -2 probably probably a the port is already in use (bind failed)
 *    -3 probably indicates socket or bind didn't work right (listen failed)
 */

int get_master_socket()
{
  struct sockaddr_in my_address;
  /* my_socket is a socket descriptor. Like a file descriptor,
   * this is an integer that indicates which socket we are connected to. 
   */
  int my_socket;
  /* Define our "well known" port number. Since this assignment is being run
   * by a large number of students we need a different well known port for 
   * each student, so we use their Unix user id to generate the port number.
   */
  u_short well_known_port = htons(6000 + getuid());
  /* get a socket allocated */
  my_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (my_socket < 0) {
    perror("server: couldn\'t build socket\n");
    return -1 ;
  }
  /* bind the socket to the well-known port on our machine */
  my_address.sin_family = AF_INET;
  my_address.sin_addr.s_addr = INADDR_ANY;
  my_address.sin_port = well_known_port;
  if (bind(my_socket, (struct sockaddr *) &my_address, sizeof(my_address))< 0) {
    perror("server: couldn\'t bind socket\n");
    return -2 ;
  }
#ifdef DEBUG
  fprintf(stderr, "server: Master socket descriptor %d\n", my_socket);
  fprintf(stderr, "  Using: address: %x, port %d\n", 
    my_address.sin_addr.s_addr,ntohs(my_address.sin_port));
#endif
  if (listen(my_socket, 5) < 0) {
    perror("server: error on listen\n");
    return -3;
  }
  return my_socket;
}

/* ************************************************************* */
/* Get a connect from another process (on another machine).
 *  When we are successful, we return a descriptor for that connection.
 *  On error a negative number is returned:
 *    -1 indicates the connect call failed
 */

int get_connection(master_socket)
  int master_socket;
{
  int client_connection;
  int len;
  struct sockaddr_in his_address;
  struct sockaddr_in my_address;
  len = sizeof(his_address);
  client_connection = accept(master_socket, 
    (struct sockaddr *) &his_address, &len);
  /* A -1 could indicates an error. We indicate this */
  if (client_connection < 0) {
    perror("server: couldn\'t accept\n"); 
    return -1;
  }
#ifdef DEBUG
  /* Report the machine and port that the the client is on.  As well
   * as our name and the local port allocated to talking to this client */
  printf("server: has connection\n");
  print_socket(client_connection);
  print_remote(client_connection);
#endif
  return client_connection;
}

/* ************************************************************* */
main(){
  int master_socket;
  int i;
  int client_connection;
  char message[80];
  if ((master_socket = get_master_socket()) < 0) {
    /* failed to get the master socket */
    exit(-1);
  }
  /* get messages from 3 clients, one message per client */
  for (i=0; i<3; i++) {
    /* get the connection to the client */
    if ((client_connection = get_connection(master_socket)) < 0) {
      exit(-1);
    }
    /* get the message from the client */
    read(client_connection,message,80);
    /* print the message */
    printf(">> %s\n",message);
    /* load up and send a reply */
    strcpy(message,"Server replies");
    write(client_connection, message, 80);
    /* close the connection with this client */
    close(client_connection);
  }
  /* close the master socket */
  close(master_socket);
}
