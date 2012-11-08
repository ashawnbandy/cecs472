/*
 * A. Shawn Bandy
 * CECS 472
 * Assignment 18 - XDR Receiver
 * 11/05/2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include "passiveUDP.c"
#include "get_port.c"

/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[]){
  int sock;
  int test_number_a;
  int test_number_b;
  float test_number_c;
  char test_string_x[80];
  char * test_string = test_string_x;
  char buffer[80];

  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* Get a socket (UDP) */ 
  sock = passiveUDP(get_port());
  read(sock, buffer, 80);
  close(sock);
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, 80, XDR_DECODE);
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  xdr_wrapstring(xdrstream, &test_string);
  printf("%d, %d, %f %s\n", test_number_a, test_number_b, test_number_c, test_string);
  /* send the message */
  xdr_destroy(xdrstream);
  return 0;
}
