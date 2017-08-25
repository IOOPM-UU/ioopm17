#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <xlocale.h>
#include <wctype.h>
#include <wchar.h>
#include <assert.h>

#define SVENSKA "sv_SE.UTF-8"

static bool initialised = false;
#define INIT                                       \
  if (initialised == false)                        \
    {                                              \
      char *locale = setlocale(LC_CTYPE, SVENSKA); \
      assert(strcmp(locale, SVENSKA) == 0);        \
      initialised = true;                          \
    }                                              \
  

wchar_t *str_to_wstr(const char *str)
{
  assert(str);
  INIT;

  // Överapproximerar målsträngens längd
  size_t   len = strlen(str);
  wchar_t *buf = calloc(len + 1, sizeof(wchar_t));

  for (int pos = 0, i = 0; pos < len; ++i)
    {
      pos += mbtowc(&buf[i], &str[pos], MB_CUR_MAX);
    }

  // Skapar en kopia av rädd längd
  wchar_t *result = wcsdup(buf);
  free(buf);

  return result;
}

char *wstr_to_str(wchar_t *wstr)
{
  assert(wstr);
  INIT;
  
  size_t len = wcslen(wstr);
  char *buf = calloc(len + 1, sizeof(char));
  unsigned int pos = 0;
  
  for (int i = 0; i < len; ++i)
    {
      pos += wctomb(&buf[pos], wstr[i]);
    }

  return buf;
}

int main(int argc, char *argv[])
{
  // Skapa en sträng med svenska tecken
  char *swe_str = "aaoåääÅÄÖ";

  // Vad anser strlen att den har för längd? (multibyte...)
  printf("'%s' har %d tecken\n", swe_str, (int) strlen(swe_str));

  // Skriv ut varje tecken (gör inte så här!)
  for (int i = 0; i < strlen(swe_str); ++i)
    {
      printf("isalpha(%c) = %s\n", swe_str[i], (isalpha(swe_str[i]) ? "true" : "false"));
    }

  // Konvertera till en array av wide chars

  wchar_t *wstr = str_to_wstr(swe_str);

  // Notera %S för att skriva ut en wide string i en printf
  printf("'%S' har %d tecken\n", wstr, (int) wcslen(wstr));
  // wcslen för att ta längden av en wide string

  // Notera %C för att skriva ut wide characters i en printf
  for (int i = 0; i < wcslen(wstr); ++i)
    {
      printf("iswalpha(%C) = %s\n", wstr[i], (iswalpha(wstr[i]) ? "true" : "false"));
    }

  // Konvertera tillbaka
  char *str = wstr_to_str(wstr);
  // Utskrift som multi-byte character fungerar fint, men inte strlen
  printf("'%s' har %d tecken\n", str, (int) strlen(str));
  return 0;
}
