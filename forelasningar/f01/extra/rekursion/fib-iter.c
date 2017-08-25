#include<stdio.h>
#include<stdlib.h>

int fib(int n) {
  int a = 0;
  int b = 1;
  for (int i=1; i<=n; ++i) {
    int fib_i = a + b;
    a = b;
    b = fib_i;
  }
  return a;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Usage: ./fib-iter 5");
  } else {
    int n = atoi(*(argv+1));
    printf("fib(%d) = %d\n", n, fib(n));
  }
  return 0;
}
