#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

//////////////////////////////////////////////////////////////////
// Structs

typedef struct stack_node stack_node_t;

struct stack
{
  stack_node_t *top;
  int size;
};

struct stack_node
{
  void *elem;
  stack_node_t *next;
};


//////////////////////////////////////////////////////////////////
// Private functions

static
stack_node_t *stack_node_new(void *elem, stack_node_t *next)
{
  stack_node_t *result = malloc(sizeof(*result));

  assert(result);

  *result = (stack_node_t) { .elem = elem, .next = next };
  
  return result;
}

//////////////////////////////////////////////////////////////////
// Public functions

void *stack_pop(stack_t *s)
{
  stack_node_t *n = s->top;
  void *elem = n->elem;

  s->top = s->top->next;
  --s->size;

  free(n);

  return elem;
}

void *stack_top(stack_t *s)
{
  return s->top->elem;
}

void stack_push(stack_t *s, void *elem)
{
  s->top = stack_node_new(elem, s->top);
  ++s->size;
}

size_t stack_size(stack_t *s)
{
  return s->size;
}

stack_t *stack_new()
{
  return calloc(1, sizeof(struct stack));
}

void stack_delete(stack_t *s)
{
  while (stack_size(s) > 0)
    {
      stack_pop(s);
    }
  free(s);
}
