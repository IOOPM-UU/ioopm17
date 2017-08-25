#include<stdio.h>
#include<stdlib.h>

// Detta deklarerar att alla förekomster av ordet "MEMO_SIZE"
// nedan ersätts med 128
#define MEMO_SIZE 128

int calculations[MEMO_SIZE];

int fib(int n) {
  // Increase the call count for fib(n)
  calculations[n]++;

  if (n == 0) {
    return 0; 
  } 
  if (n == 1) {
    return 1; 
  }
  return fib(n-1) + fib(n-2); 
}

int main(int argc, char **argv) {
  // Intialise the counts for all calculations to 0
  for (int i=0; i<MEMO_SIZE; ++i) {
    calculations[i] = 0;
  }

  int n = 0; 

  if (argc < 2) {
    puts("Usage: ./fib-count 5");
  } else {
    n = atoi(*(argv+1));
    printf("fib(%d) = %d\n", n, fib(n));
  }

  // Print the number of calculations of each fib number
  for (int i=0; i<=n; ++i) {
    // <=n instead of <MEMO_SIZE avoids stupid prints. This
    // requires that we have moved the declaration of n from line
    // 34 into the enclosing scope (here line 29). An alternate
    // solution would be to use calculations[i] instead of i<=n.
    // Why?
    printf("fib(%d) was calculated %d times\n", i, calculations[i]);
  }

  return 0;
}
