#include <stdbool.h>
#include <stdio.h>

int main(void)
{
  printf("bool           %zd\n", sizeof(bool));
  printf("char           %zd\n", sizeof(char));
  printf("short          %zd\n", sizeof(short));
  printf("int            %zd\n", sizeof(int));
  printf("long           %zd\n", sizeof(long));
  printf("long long      %zd\n", sizeof(long long));
  printf("float          %zd\n", sizeof(float));
  printf("double         %zd\n", sizeof(double));
  printf("long double    %zd\n", sizeof(long double));
  return 0;
}
