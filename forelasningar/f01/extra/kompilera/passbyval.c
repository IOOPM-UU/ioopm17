#include <stdio.h> // för printf

// ökar parametern a med ett som sido-effekt
void plus_ett(int a) { 
  a = a + 1;
}

int main() {
  int a = 0;
  for(int i = 0; i < 3; i++) {
    plusEtt(a);
    printf("%d + 1 = %d\n", i, a);
  }
  return 0;
}
