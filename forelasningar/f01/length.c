#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *s = "Hello";
  char t[5]; // Fel! För att få plats med "Hello" krävs 6 tecken
             // 5 för strängen **plus 1 för '\0'**
  strcpy(t, s);
  puts(t);
  return 0;
}