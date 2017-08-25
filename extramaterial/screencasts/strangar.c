#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char *person1  = "Captain Beefheart"; 
  char *person2  = person1;
  char person3[] = "Captain Beefheart"; 

  // Do these variables denote the same string in memory?
  printf("person1 == person2?\t\t%s\n", person1 == person2 ? "yes" : "no");
  printf("person1 == person3?\t\t%s\n", person1 == person3 ? "yes" : "no");
  printf("person2 == person3?\t\t%s\n", person2 == person3 ? "yes" : "no");

  // Do these variables point to strings of equal content?
  printf("strcmp(person1, person2)?\t%s\n", strcmp(person1, person2) ? "no" : "yes");
  printf("strcmp(person1, person3)?\t%s\n", strcmp(person1, person3) ? "no" : "yes");
  printf("strcmp(person2, person3)?\t%s\n", strcmp(person2, person3) ? "no" : "yes");

  return 0;
}
