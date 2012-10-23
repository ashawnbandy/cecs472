/* Convert a sentence to upper or lower case */
/* Next 3 lines are added for rpc */
#include <rpc/rpc.h>
#include "convert.h"
CLIENT *handle;

void upper_it(char *sentence);
void lower_it(char *sentence);

main() {
  char buffer[100]; /* holds the sentence */
  char whichway[5]; /* to upper or to lower */
  /* Addition for RPC */
  if ((handle = clnt_create("cheetah",CONVERTPROG,CONVERTVER,"tcp")) == NULL) {
    /* filed to find server, print the error message */
    clnt_pcreateerror("convert client");
    exit(-1);
  };
  /* control-C to exit */
  for (;;) {
    printf("enter the string ");
    gets(buffer);
    printf("u) to upper, l) to lower? ");
    gets(whichway);
    switch (whichway[0]) {
      case 'u':
        upper_it(buffer);
        break;
      case 'l':
        lower_it(buffer);
        break;
      default:
        printf("unrecognized option\n");
    }
    printf("%s\n", buffer);
  }
}
