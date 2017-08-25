#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int nfak = 1;
  int n = atoi(argv[1]);

  for (int i = 1; i <= n; ++i)
    {
      nfak *= i;
    }

  printf("%d! = %d\n", n, nfak);

  return 0;
}
