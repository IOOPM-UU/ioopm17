#include <stdlib.h>

struct node {
  void *element;
  struct node *next;
};

struct stack {
  struct node *top;
};

struct stack *mkStack() {
  struct stack *result = malloc(sizeof(struct stack));
  if (result) {
    result->top = NULL;
  }
  return result; 
}

struct node *mkStackNode(void *element, struct node *next) {
  struct node *result = malloc(sizeof(struct stack));
  if (result) {
    result->element = element;
    result->next    = next;
  }
  return result; 
}

void push(struct stack *s, void *e) {
  s->top = mkStackNode(e, s->top); 
}

void *pop(struct stack *s) {
  if (s->top == NULL) return NULL;

  void *element = s->top->element;
  s->top = s->top->next;
  return element;
}

void *top(struct stack *s) {
  return s->top == NULL ? NULL : s->top->element;
}

