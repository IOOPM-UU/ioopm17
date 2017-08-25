#include <stdlib.h>
#include "list.h"

struct list {
  struct node *first;
  struct node *last;
};

struct node {
  void *value;
  struct node *next;
};

struct iterator {
};

list *mkList() {
  return calloc(1, sizeof(list));
}

struct node *mkLink(struct node *n, void *v) {
  struct node *result = malloc(sizeof(struct node));
  if (result) {
    result->next = n;
    result->value = v;
  }
  return result;
}

void append(list *l, void *v) {
  if (empty(l)) {
    l->first = l->last = mkLink(NULL, v);
  } else {
    l->last = l->last->next = mkLink(NULL, v);
  }
}

void delete(list *l, int idx) {
  struct node **cursor = &(l->first);
  for (int i = 0; i < idx && *cursor; ++i) {
    cursor = &((*cursor)->next);
  }

  if (*cursor) {
    struct node *temp = *cursor;
    *cursor = (*cursor)->next;
    free(temp);
  }
}

int empty(list *l) {
  return l->last == NULL;
}

int length(list *l) {
  int length = 0;
  iterator *iter = mkIterator(l);
  while (hasMore(iter)) {
    ++length;
    next(iter);
  }
  rmIterator(iter);
  return length;
}


