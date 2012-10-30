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
  char * not_test_string = "Hello There";
  int sizeofstring = sizeof(not_test_string)+1;
  char * test_string;
  int sizeofbuffer = sizeof(int) + sizeof(int) + sizeof(float) + sizeofstring;
  char buffer[sizeofbuffer+1];

  XDR xdrobject;
  XDR *xdrstream = &xdrobject;
  /* Get a socket (UDP) */
  sock = passiveUDP(get_port());
  read(sock, buffer, sizeof(buffer));
  close(sock);
  /* XDR a message */
  xdrmem_create(xdrstream, buffer, sizeof(buffer), XDR_DECODE);
  xdr_int(xdrstream, &test_number_a);
  xdr_int(xdrstream, &test_number_b);
  xdr_float(xdrstream, &test_number_c);
  printf("(recv) string success? %i\n",xdr_string(xdrstream, &test_string, sizeof(not_test_string)));
  printf("%d, %d, %f, %s\n", test_number_a, test_number_b, test_number_c, test_string);
  /* send the message */
  xdr_destroy(xdrstream);
  return 0;
}