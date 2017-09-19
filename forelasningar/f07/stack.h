#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack stack_t;

void *stack_pop(stack_t *s);
void *stack_top(stack_t *s);
void stack_push(stack_t *s, void *elem);
size_t stack_size(stack_t *s);
stack_t *stack_new();
void stack_delete(stack_t *s);

#endif
