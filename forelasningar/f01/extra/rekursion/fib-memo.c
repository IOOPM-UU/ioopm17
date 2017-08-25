#include<stdio.h>
#include<stdlib.h>

// Detta deklarerar att alla förekomster av ordet "MEMO_SIZE"
// nedan ersätts med 128
#define MEMO_SIZE 128

int memoised_fib_values[MEMO_SIZE];

int fib(int n) {
  if (n == 0) {
    return 0; 
  } 
  if (n == 1) {
    return 1; 
  }

  int cached = memoised_fib_values[n];
  if (!cached) {
    cached = fib(n-1) + fib(n-2); 
    memoised_fib_values[n] = cached;
  }

  return cached;
}

int main(int argc, char **argv) {
  // Intialise all memoised_fib_values to 0
  for (int i=0; i<MEMO_SIZE; ++i) {
    memoised_fib_values[i] = 0;
  }

  if (argc < 2) {
    puts("Usage: ./fib-memo 5");
  } else {
    int n = atoi(*(argv+1));
    printf("fib(%d) = %d\n", n, fib(n));
  }

  return 0;
}
