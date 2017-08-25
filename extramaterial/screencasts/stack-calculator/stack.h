#include <stdbool.h>

typedef struct stack stack;

// Make a new stack
stack *stack_new();

// Remove a stack from memory
void stack_free(stack *s);

// Push elem to s
void stack_push(stack *s, void *elem);

// Pop an element from s. Returns NULL if s is empty
void *stack_pop(stack *s);

// Return the top element of s. Returns NULL if s is empty
void *stack_top(stack *s);

// Return the number of elements in the stack
int stack_size(stack *s);

// An iterator for the stack
typedef struct iterator iter_t;

// Initialize an iterator
iter_t *iterator_new(stack *s);

// Return current element and move i forward
void *iterator_next(iter_t *i);

// true if i has more elements, false otherwise
bool iterator_more(iter_t *i);

// Remove an iterator from memory
void iterator_free(iter_t *i);