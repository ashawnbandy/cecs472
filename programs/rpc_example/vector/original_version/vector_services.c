#include "vectora.h"
void add(struct vector *a, struct vector *b, struct vector *c) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
}
