#include <stdlib.h>

struct person{
  char *first;
  char *last;
};

struct person *mk_person(char *first, char *last){
  struct person *p = malloc(sizeof(struct person));
  if(!p)
    {
      return NULL;
    }
  p->first = first;
  p->last = last;
  return p;
}

char *get_first_name(struct person *p){
  return p->first;
}

char *get_last_name(struct person *p){
  return p->last;
}
