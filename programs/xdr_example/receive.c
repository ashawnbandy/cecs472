#include <stdio.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include "passiveUDP.c"
/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[]){
  int sock;
  int test_number_a;
  int test_number_b;
  float test_number_c;
  char buffer[80];
  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* Get a socket (UDP) */ 
  sock = passiveUDP("7654");
  read(sock, buffer, 80);
  close(sock);
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, 80, XDR_DECODE);
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  printf("%d, %d, %f\n", test_number_a, test_number_b, test_number_c);
  /* send the message */
  xdr_destroy(xdrstream);
  return 0;
}
