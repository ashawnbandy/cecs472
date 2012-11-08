/*
 * A Shawn Bandy F1
 * CECS 472
 * Assignment 18 - Sender
 * 11/05/2012
 */

#include <rpc/types.h>
#include <rpc/xdr.h>
#include "connectUDP.c"
#include "get_port.c"

/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[]){
  int sock;
  int test_number_a = 6;
  int test_number_b = 47;
  float test_number_c = -34.5;
  char * test_string = "Hello there.";

  char buffer[80];
  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, 80, XDR_ENCODE);
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  xdr_wrapstring(xdrstream, &test_string);
  /* Get a socket (UDP) */ 
  sock = connectUDP("localhost", get_port());
  /* send the message */
  write(sock, buffer, 80);
  xdr_destroy(xdrstream);
  close(sock);
  return 0;
}
