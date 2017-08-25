#include <stdio.h>
#include <string.h>

int length(char *s)
{
  int count = 0;
  while(s[count] != '\0')
    {
      ++count;
    }
  return count;
}

int main(int argc, char *argv[])
{
  char *s = "Hello";
  char t[length(s) + 1]; // Ännu hellre strlen(s) + 1
  strcpy(t, s);
  puts(t);
  return 0;
}