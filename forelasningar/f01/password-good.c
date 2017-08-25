#include <stdio.h>

int main (void)
{
  char password[] = "abc123";
  char *entered;       // kommer att ”peka ut” inläst data
  size_t entered_size; // längden på entered

  puts("Please enter the secret code:");
  getline(&entered, &entered_size, stdin); // read input

  if (strncmp(entered, password, entered_size) == 0)
    {
      puts("You are logged in!");
    }
  else
    {
      puts("Incorrect password!");
    }

  return 0;
}
