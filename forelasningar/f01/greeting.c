#include<stdio.h>

int main()
{
  char buffer[128];
  char first[128];
  char last[128];

  puts("What is your first name?");
  scanf("%s", buffer);
  first = buffer; // Fel! first och buffer är nu **samma* sträng

  puts("What is your last name?");
  scanf("%s", buffer); // När vi ändrar buffer här ändrar vi samtidigt first!
  last = buffer; // Fel! first, last och buffer är nu **samma* sträng

  printf("Hello %s %s!\n", first, last);
  return 0;
}