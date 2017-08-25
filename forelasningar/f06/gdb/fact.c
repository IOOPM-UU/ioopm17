#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
  if(n == 0)
    {
    return 0;
    }
  int fact = factorial(n-1);
  return n * fact;
}

int main(int argc, char *argv[]){
  if(argc < 2)
    puts("Usage: fact n");
    return 1;
  int n = atol(argv[1]);
  int fact = factorial(n);
  printf("%d! = %d\n", n, fact);
  return 0;
}