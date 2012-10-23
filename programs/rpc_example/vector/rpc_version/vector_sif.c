#include <rpc/rpc.h>
#include "vectora.h"
#include "vector.h"
void add(struct vector *a, struct vector *b, struct vector *c);

answer *add_1_svc(pass *param, struct svc_req* dummy) {
  struct vector p,q,r;
  static struct answer result;
  /* unpack the parameters */
  p.x = param->data[0];
  p.y = param->data[1];
  q.x = param->data[2];
  q.y = param->data[3];
  /* call the actual procedure */
  add(&p,&q,&r);
  /* pack up the answer */
  result.data[0] = r.x;
  result.data[1] = r.y;
  /* return the answer */
  return &result;
}
