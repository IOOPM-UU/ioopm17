#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char c = getchar();
  while(c != EOF)
    {
    if(c == '.')
      {
        putchar('!');
      }
    else if(c == '?')
      {
        putchar('?');
        putchar('!');
      }
    else
      {
        putchar(toupper(c));
      }
    c = getchar();
    }
  return 0;
}
