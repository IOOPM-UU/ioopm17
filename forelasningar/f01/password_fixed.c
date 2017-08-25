#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool equals(char *s1, char *s2)
{
  int i = 0;
  while(s1[i] != '\0')
    {
    if(s1[i] != s2[i])
      {
        return false;
      }
    i++;
    }
  return s1[i] == s2[i];
}

int main()
{
  char *password = "abc123";
  char entered[128];

  puts("Please enter the secret code:");
  scanf("%s", entered); // read input

  if(equals(entered, password)) // Ännu hellre strncmp(s1, s2, strlen(entered)) == 0
    {
      puts("You are logged in!");
    }
  else
    {
      puts("Incorrect password!");
    }
  return 0;
}