#include <rpc/rpc.h>
#include "convert.h"
/* convert_cif.c;
 * Client side interface for rpc calls.
 * By modifying convert_services.c
 * WARNING: this file and the convert_services.c both give definitions for 
 *  upper_it and lower_it. Do not compile both on the same machine.
*/
extern CLIENT *handle;
void upper_it(char *sentence){
  char **buffer;
  buffer = upper_it_1(&sentence, handle);
  strcpy(sentence, *buffer);
}
void lower_it(char *sentence){
  char **buffer;
  buffer = lower_it_1(&sentence, handle);
  strcpy(sentence, *buffer);
}
