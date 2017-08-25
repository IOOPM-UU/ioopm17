#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
  if(argc < 2){
    puts("Missing file name!");
    return -1;
  }

  char* infile = argv[1];
  char outfile[strlen(infile) + 5];
  strcpy(outfile, "lin_");
  strcat(outfile, infile);
  FILE* in = fopen(infile, "r");
  FILE* out = fopen(outfile, "w");

  int line = 1;
  char buffer[128];
  while(fgets(buffer, 128, in)){
    fprintf(out, "%d. %s", line, buffer);
    line++;
  }
  fclose(in);
  fclose(out);
  return 0;
}