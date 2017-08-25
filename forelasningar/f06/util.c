#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void strip(char *s)
{
  int len = strlen(s);
  int i = len - 1;
  while(isspace(s[i]))
    {
      i--;
    }
  s[i+1] = '\0';
}

char *ask_question_string(char *q)
{
  char *answer = NULL;
  size_t length;
  puts(q);
  getline(&answer, &length, stdin);
  strip(answer);
  return answer;
}
