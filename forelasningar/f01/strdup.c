char *strdup(const char *str)
{
  char *dup = malloc(strlen(str)+1);
  char *cursor = dup;

  while (*str)
    {
      *cursor = *str;
      ++str;
      ++cursor;
    }
  *cursor = '\0';

  return dup;
}
