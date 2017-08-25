#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void readline(char dest[128]){
  fgets(dest, 128, stdin);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void showStack(stack *s){
  iter_t *i = iterator_new(s);
  while(iterator_more(i)){
    int *elem = (int*)iterator_next(i);
    printf("%d", *elem);
    if(iterator_more(i)){
      printf(", ");
    }
  }
  printf(" <-- Stack\n");
  iterator_free(i);
}

void pushNum(stack *s, int num){
  int *elem = malloc(sizeof(int));
  *elem = num;
  stack_push(s, elem);
}

void doAdd(stack *s){
  if(stack_size(s) < 2){
    puts("*** ERROR: Not enough arguments ***");
  }else{
    int *arg1 = (int*)stack_pop(s);
    int *arg2 = (int*)stack_pop(s);
    int *result = malloc(sizeof(int));
    *result = *arg1 + *arg2;
    stack_push(s, result);
    free(arg1);
    free(arg2);
  }
}

void doMultiply(stack *s){
  if(stack_size(s) < 2){
    puts("*** ERROR: Not enough arguments ***");
  }else{
    int *arg1 = (int*)stack_pop(s);
    int *arg2 = (int*)stack_pop(s);
    int *result = malloc(sizeof(int));
    *result = *arg1 * *arg2;
    stack_push(s, result);
    free(arg1);
    free(arg2);
  }
}

int main(){
  stack *s = stack_new();
  char buffer[128];
  strcpy(buffer, "abc");
  while(strlen(buffer) > 0){
    puts("================");
    showStack(s);
    puts("");
    readline(buffer);

    if(strcmp(buffer, "+") == 0){
      doAdd(s);
    }
    else if(strcmp(buffer, "*") == 0){
      doMultiply(s);
    }
    else if(isdigit(buffer[0])){
      int num = atoi(buffer);
      pushNum(s, num);
    }
    else if(strlen(buffer) > 0){
      printf("*** ERROR: Unknown command '%s' ***\n", buffer);
    }
  }
  stack_free(s);
  return 0;
}
