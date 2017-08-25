#include <string.h>
#include <stdio.h>
#include "person.h"
#include "util.h"

int main(int argc, char *argv[]){
  struct person *p = mk_person("Elias", "Castegren");
  char *first = get_first_name(p);
  char *last = get_last_name(p);
  if (strcmp(first, "Elias") == 0 &&
      strcmp(last, "Castegren") == 0){
    puts("Test of person module passed!");
  } else {
    puts("Test of person module failed!");
  }

  char *answer = ask_question_string("Please write the correct answer:");
  if (strcmp(answer, "The correct answer") == 0){
    puts("Test of ask_question_string passed!");
  } else {
    puts("Test of ask_question_string failed!");
  }
  return 0;
}