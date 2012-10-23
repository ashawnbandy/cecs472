#include <rpc/types.h>
#include <rpc/xdr.h>
#include "connectUDP.c"
/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[]){
  int sock;
  int test_number_a = 6;
  int test_number_b = 47;
  float test_number_c = -34.5;
  char buffer[80];
  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, 80, XDR_ENCODE);
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  /* Get a socket (UDP) */ 
  sock = connectUDP("aardvark", "7654");
  /* send the message */
  write(sock, buffer, 80);
  xdr_destroy(xdrstream);
  close(sock);
  return 0;
}
