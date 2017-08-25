#include <stdio.h>

int main()
{
  for(int c = 0; c < 128; c++) // OBS! c kan inte vara en char,
                               // eftersom en char bara rymmer 1
                               // byte, alltså som mest värdet 127!
    {
      printf("Nr: %d, Char: %c\n", c, c);
    }
  return 0;
}
