#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct set set_t;

struct set
{
  int size;
  uint64_t *elements;
};

set_t *set_new(int size)
{
  set_t *result = calloc(1, sizeof(struct set));
  result->size = size;
  result->elements = calloc(size / 64 + 1, sizeof(bool));

  return result;
}

void set_add(set_t *s, int element)
{
  s->elements[element / 64] |= 1UL << (element % 64);
}

void set_remove(set_t *s, int element)
{
  s->elements[element / 64] &= ~(1UL << (element % 64));
}

bool set_has(set_t *s, int element)
{
  return s->elements[element / 64] & 1UL << (element % 64);
}

int set_size(set_t *s)
{
  return s->size;
}

set_t *set_union(set_t *a, set_t *b)
{
  set_t *result = set_new(set_size(a));
  for (int i = 0; i < set_size(a); ++i)
    {
      if (set_has(a, i) || set_has(b, i))
        set_add(result, i); 
    }
  return result;
}

set_t *set_union2(set_t *a, set_t *b)
{
  set_t *result = set_new(set_size(a));
  for (int i = 0; i < set_size(a) / 64; ++i)
    {
      result->elements[i] = a->elements[i] | b->elements[i]; 
    }
  return result;
}
