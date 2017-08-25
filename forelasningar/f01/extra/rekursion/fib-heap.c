#include<stdio.h>
#include<stdlib.h>

int *heap_int(int i)
{
  int *result = malloc(sizeof(int));
  *result = i;
  return result;
}

int *fib(int *n)
{
  if (*n == 0)
    {
      return heap_int(0);
    }
  else
    {
      if (*n == 1)
	{
	  return heap_int(1);
	}
      else
	{
	  return heap_int(*fib(heap_int(*n-1)) + *fib(heap_int(*n-2)));
	}
    }
}

// OBSERVERA!
// Detta program läcker minne som ett såll -- det frigör inte några allokerade pekare
int main(int argc, char **argv)
{
  if (argc < 2)
    {
      puts("Usage: ./fib-rec 5");
    }
  else
    {
      int *n = heap_int(atoi(*(argv+1)));
      printf("fib(%d) = %d\n", *n, *fib(n));
    }
  return 0;
}
