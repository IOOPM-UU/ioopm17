#include<stdio.h>
#include<string.h>

void copy(char *s1, char *s2)
{
  for(int i = 0; s2[i] != '\0'; i++)
    {
      s1[i] = s2[i];
    }
}

int main(){
  int MAX_LEN = 128;
  char buffer[MAX_LEN];
  char first[MAX_LEN];
  char last[MAX_LEN];

  puts("What is your first name?");
  scanf("%s", buffer);
  copy(first, buffer); // Ännu hellre strncpy(first, buffer, MAX_LEN)

  puts("What is your last name?");
  scanf("%s", buffer);
  copy(last, buffer); // Ännu hellre strncpy(last, buffer, MAX_LEN)

  printf("Hello %s %s!\n", first, last);
  return 0;
}