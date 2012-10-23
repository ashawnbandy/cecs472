#include <rpc/rpc.h>
#include "vectora.h"
#include "vector.h"
extern CLIENT *handle;

void add(struct vector *a, struct vector *b, struct vector *c) {
  struct pass params;
  struct answer *result;
  /* pack up the parameters a and b */
  params.data[0] = a->x;
  params.data[1] = a->y;
  params.data[2] = b->x;
  params.data[3] = b->y;
  /* call the remote function */
  result = add_1(&params, handle);
  /* unpack the answer into c */
  c->x = result->data[0];
  c->y = result->data[1];
}
