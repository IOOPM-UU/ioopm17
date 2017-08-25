#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define bufsiz 2048

int count_words(char *fn) {
  FILE  *f         = fopen(fn, "r");
  char  *buffer    = malloc(bufsiz);
  int    words     = 0;
  int    bytesread = 0;
  int    more      = 1;

  do {
    bytesread = fread(buffer, 1, bufsiz, f);
    
    if (bytesread < bufsiz) more = 0;
    
    for (int i=0; i < bytesread; ++i) {
      if (isalpha(buffer[i])) continue; 

      ++words; 

      while (!isalpha(buffer[i]) && i < bytesread) ++i; 
    }

  } while (more);

  printf ("\t%d\t%s\n", words, fn);

  free(buffer);

  return words;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Usage ./wordcount file1 file2 ...");
  } else {
    unsigned int total = 0;
    while(*++argv) {
      total += count_words(*argv);
    }
    printf ("\t%d\ttotal\n", total);
  }
  return 0;
}
