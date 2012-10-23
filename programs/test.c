#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/file.h>
#include <stdlib.h>
#include <string.h>  /* memset */
int main() {
  int master_socket;
  int client_connection;
  int len;
  int result;
  int readcount;
  char message[80];
  struct sockaddr_in his_address;
  struct sockaddr_in my_address;
  /* Set up our internet address structure */
  memset( &my_address, 0, sizeof(my_address) );
  my_address.sin_family = AF_INET;
  my_address.sin_port = 8282;
  my_address.sin_addr.s_addr = INADDR_ANY;
  /* Set up the internet socket and make the connection */
  master_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (master_socket < 0 ) {
    perror("server: couldn't build master socket");
    exit(-1);
  }
  if (bind(master_socket, (struct sockaddr *) &my_address,
      sizeof(my_address))< 0) {
    perror("server: couldn\'t bind socket");
    exit(-1) ;
  }
  if (listen(master_socket, 5) < 0) {
    perror("server: error on listen");
    exit(-1);
  }
  printf("ready to accept\n");
  if ( (client_connection = accept(master_socket,
        (struct sockaddr *) &his_address, &len) ) < 0) {
    perror("server: couldn\'t accept");
    exit(-1);
  }

  /* Echos to the screen until EOF or error */
  while ( ( readcount = read(client_connection, message, sizeof(message)) )
          <= 0 ) {
    write(1, message, readcount);
  }
  close(client_connection);
  close(master_socket);
  return 0;
}
