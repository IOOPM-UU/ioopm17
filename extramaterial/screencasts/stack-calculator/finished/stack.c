#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct node{
  void *elem;
  struct node *next;
};

struct node *node_new(void *element, struct node *next){
  struct node *n = malloc(sizeof(struct node));
  if(n == NULL)
    return NULL;
  n->elem = element;
  n->next = next;
  return n;
}

struct stack{
  struct node *top;
};

struct stack *stack_new(){
  struct stack *s = malloc(sizeof(struct stack));
  if(s == NULL)
    return NULL;
  s->top = NULL;
  return s;
}

void stack_free(struct stack *s){
  assert(s != NULL);
  struct node *cursor = s->top;
  while(cursor != NULL){
    struct node *tmp = cursor;
    cursor = cursor->next;
    free(tmp);
  }
  free(s);
}

void stack_push(struct stack *s, void *elem){
  assert(s != NULL);
  struct node *newTop = node_new(elem, s->top);
  s->top = newTop;
}

void *stack_pop(struct stack *s){
  assert(s != NULL);
  if(s->top == NULL)
    return NULL;
  struct node *tmpNode = s->top;
  s->top = s->top->next;
  void *result = tmpNode->elem;
  free(tmpNode);
  return result;
}

void *stack_top(struct stack *s){
  assert(s != NULL);
  if(s->top == NULL)
    return NULL;
  return s->top->elem;
}

int stack_size(struct stack *s){
  assert(s != NULL);
  int counter = 0;
  struct node *cursor = s->top;
  while(cursor != NULL){
    counter++;
    cursor = cursor->next;
  }
  return counter;
}

// Nedan finns koden för en stackiterator. En iterator fungerar
// som en pekare in en annan datastruktur, och kan användas för
// att iterera genom datastrukturens alla element utan att man
// behöver veta hur strukturen ser ut på insidan. En iterator
// erbjuder i allmänhet två operationer:
//
//  * hasNext returnerar true (eller 1) om det finns fler element
//    att peka ut, annars false (eller 0). I vårt fall kollar vi
//    helt enkelt om stacknoden vi för närvarande pekar ut är
//    NULL.
//
//  * getNext returnerar elementet för den nod som vi för
//    närvarande pekar ut OCH flyttar iteratorn till nästa nod.
//    Notera att vi inte returnerar stackens noder, utan elementen
//    som varje nod pekar ut (annars skulle abstraktionen läcka!).
//    Den typiska användningen är att man bara anropar getNext om
//    hasNext returnerar true.
//
// Se koden för showStack i calc.c för ett exempel på hur en
// iterator kan användas.

struct iterator{
  struct node *current;
};

struct iterator *iterator_new(struct stack *s){
  assert(s != NULL);
  struct iterator *i = malloc(sizeof(struct iterator));
  if(i == NULL)
    return NULL;
  i->current = s->top;
  return i;
}

bool iterator_more(struct iterator *i){
  assert(i != NULL);
  if(i->current != NULL)
    return true;
  else
    return false;
}

void *iterator_next(struct iterator *i){
  assert(i != NULL);
  struct node *tmp = i->current;
  i->current = i->current->next;
  return tmp->elem;
}

void iterator_free(struct iterator *i){
  assert(i != NULL);
  free(i);
}