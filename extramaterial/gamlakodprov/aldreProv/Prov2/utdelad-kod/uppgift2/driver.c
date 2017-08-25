#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int *mkIntCell(int i) {
  int *result = malloc(sizeof(int));
  *result = i;
  return result;
}

int main(int argc, char *argv[]) {
  list *l = mkList();
  append(l, mkIntCell(1));
  append(l, mkIntCell(4));
  append(l, mkIntCell(91));
  iterator *i = mkIterator(l);
  int sum = 0;
  while (hasMore(i)) {
    sum += *(int*) next(i);
  }
  printf("Summa: %d\n", sum);
  rmIterator(i);
  rmList(l);
  return 0;
}
