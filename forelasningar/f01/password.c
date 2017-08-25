#include <stdio.h>
#include <stdbool.h>

int main()
{
  char *password = "abc123";
  char entered[128];

  puts("Please enter the secret code:");
  scanf("%s", entered); // läs ett ord från användaren

  if(entered == password) // "är entered och password **samma** sträng?"
                          // inte "är entered och password **likadana**?"
    {
      puts("You are logged in!");
    }
  else
    {
      puts("Incorrect password!");
    }
  return 0;
}