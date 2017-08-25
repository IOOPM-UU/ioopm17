#include <stdio.h>

int main()
{
  char buffer[128];
  puts("What is your name?");
  scanf("%s", buffer);
  printf("Hello %s! You are looking good!\n", buffer);
  return 0;
}