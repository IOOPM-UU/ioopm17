/* Demoprogram för gdb-presenation *:58 HT07        */
/* Programet skriver ut sina kommandoradsargument   */
/* på stdout ett argument per rad                   */
/* Används för att visa hantering av kommandorads-  */
/* argument vid debugging med GDB                   */

#include <stdio.h>

int main(int argc, char **argv){
  int i;

  for(i=0; i<argc; i++)
    printf("%s\n", argv[i]);

  return 0;
}
