#include <stdio.h>
#include <ctype.h>
#include <string.h>

void cheer(char name[]){
  int len = strlen(name);
  char newName[len + 1];
  strncpy(newName, name, len + 1);
  for(int i = 0; newName[i] != '\0'; ++i){
    char letter = newName[i];
    printf("Ge mig ett '%c'!\n", tolower(letter));
    printf("%c!\n", toupper(letter));
  }
  puts("Vad blir det?");
  for (int i = 0; newName[i] != '\0'; ++i){
    newName[i] = toupper(newName[i]);
  }
  puts(newName);
}

int main(){
  char name[] = "Uppsala";
  cheer(name);
  return 0;
}