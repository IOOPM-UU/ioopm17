#include "stack.c"

int main(int argc, char *argv[]) {
  struct stack *s = mkStack();
  void *tmp = NULL;

  push(s, malloc(1024));
  push(s, malloc(2048));

  tmp = pop(s);
  free(tmp);

  push(s, malloc(4096));
  tmp = pop(s);
  free(tmp);
  tmp = pop(s);
  free(tmp);
  free(s);
  return 0;
}
