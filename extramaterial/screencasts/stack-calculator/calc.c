#include <stdio.h>
#include <string.h>
#include "stack.h"

#define MAX_LEN 128

void readline(char dest[MAX_LEN]){
  fgets(dest, MAX_LEN, stdin);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

int main(){
  char buffer[MAX_LEN];
  // TODO: Allocate the stack
  strcpy(buffer, "abc");
  while(strlen(buffer) > 0){
    puts("================");
    // TODO: Print the stack
    puts("");
    readline(buffer);
    // TODO: Support more commands
    if(strlen(buffer) > 0){
      printf("*** ERROR: Unknown command '%s' ***\n", buffer);
    }
  }
  // TODO: Free the stack
  return 0;
}
