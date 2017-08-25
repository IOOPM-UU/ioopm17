#include <stdio.h>

int main()
{
  char *names[] = {"Tobias Wrigstad", "Elias Castegren", "Fredrik Wahlberg"};
  int   rooms[] = {1356, 1357, 2150};
  int length = 3;
  for (int i = 0; i < length; ++i){
    printf("%s sitter i %d\n", names[i], rooms[i]);
  }
  return 0;
}