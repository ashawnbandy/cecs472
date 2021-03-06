
/*
 * A. Shawn Bandy F1
 * Assignment 18 - Sender
 * CECS472
 * 10/29/2012
 */

#include <rpc/types.h>
#include <rpc/xdr.h>
#include "connectUDP.c"
#include "get_port.c"

/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[]){

	char * service = get_port();
	char * host = "localhost";

        switch (argc) {
        case 1:
                break;
        case 3:
                service = argv[2];
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: <?> [host [port]]\n");
                exit(1);
        }



  int sock;
  char * test_string = "Hello there";
  char buffer[1024];


  int test_number_a = 6;
  int test_number_b = 47;
  float test_number_c = -34.5;
 
  printf("%s\n",test_string);
  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, sizeof(buffer), XDR_ENCODE);
  
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  
  
  printf("(send) xdr string works? %i\n",xdr_wrapstring(xdrstream, &test_string));
  /* Get a socket (UDP) */ 
  sock = connectUDP(host, service);
  /* send the message */
  write(sock, buffer, sizeof(buffer));
  xdr_destroy(xdrstream);
  close(sock);
  return 0;
}
