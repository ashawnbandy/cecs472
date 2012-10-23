#include <rpc/rpc.h>
#include "convert.h"
/* convert_svc_stubs.c;
 * Server side stubs for rpc calls.
*/
void upper_it(char *sentence);
void lower_it(char *sentence);
static char buffer[100];
static char *bufptr = buffer;
/* Convert a sentence to upper or lower case */
char **upper_it_1_svc(char **sentence, struct svc_req *dummy){
  strcpy(buffer, *sentence);
  upper_it(buffer);
  return &bufptr;
}
char **lower_it_1_svc(char **sentence, struct svc_req *dummy){
  strcpy(buffer, *sentence);
  lower_it(buffer);
  return &bufptr;
}
