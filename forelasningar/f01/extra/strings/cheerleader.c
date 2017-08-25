#include <stdio.h>

void cheer(char name[]){
  for(int i = 0; name[i] != '\0'; ++i){
    char letter = name[i];
    printf("Ge mig ett '%c'!\n", letter);
    printf("%c\n", letter);
  }
  puts("Vad blir det?");
  puts(name);
}

int main(int argc, char *argv[]){
  char name[] = "Uppsala";
  cheer(name);
  return 0;
}