/* Vector operations interface */
#include <rpc/rpc.h>
#include "vector.h"
CLIENT *handle;
#include "vectora.h"
void add(struct vector *a, struct vector *b, struct vector *c);
int main() {
    struct vector p,q,r;
     if ((handle = clnt_create("cheetah",
      VECTORPROG, VECTORVER, "tcp")) == NULL) {
        /* couldn't connect to the server */
        clnt_pcreateerror("vector client");
        exit(-1);
    }
    p.x = 1;
    p.y = 4;
    q.x = 2;
    q.y = 5;
    add(&p, &q, &r);
    printf("answer (should be (3, 9)): %d, %d\n", r.x, r.y);
    return 0;
}
