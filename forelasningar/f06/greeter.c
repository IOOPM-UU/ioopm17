#include <stdio.h>

#include "util.h"
#include "person.h"

int main(void)
{
  char *first = ask_question_string("What is your first name?");
  char *last = ask_question_string("What is your last name?");
  struct person *p = mk_person(first, last);
  printf("Greetings %s of the glorious %s family!!\n",
         get_first_name(p), get_last_name(p));
  // TODO: free the allocated person
  return 0;
}
