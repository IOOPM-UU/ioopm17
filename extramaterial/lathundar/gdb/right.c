/* Demoprogram för gdb-presenation *:58 HT07     */
/* Detta program har inga avsiktliga fel, men    */
/* funktionen printlist för utskrift av den      */
/* länkade listan är inte implementerad.         */
/* Programmet används för att demonstrera        */
/* grundläggande GDB-kommandon                   */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct post{
  int nr;
  char *data;
  struct post *next;
} Post;

const char *strings[]={"STEFAN","HUGO","JOZEF","RICKARD",
		      "PER","OLA","TOBIAS","JOACHIM"};
const int antal=sizeof(strings)/sizeof(char *);

char *strtoupper(char *str){
  int i;
  for(i=0; i<strlen(str); i++)
    str[i]=toupper(str[i]);
  return str;
} /* strtoupper */

Post *makelist(void){
  Post *first=NULL, *last=NULL, *ny=NULL;
  int i;
  for(i=0; i<antal; i++){
    ny=malloc(sizeof(Post));
    ny->nr=i;
    ny->data=malloc(strlen(strings[i])+1);
    strcpy(ny->data, strings[i]);
    if (first==NULL) last=first=ny;
    else last=last->next=ny;
  } /* for */
  return first;
} /* makelist */

Post *find(Post *first, char *str){
  Post *tmp;
  for(tmp=first; tmp!=NULL; tmp=tmp->next)
    if (strcmp(tmp->data, str)==0)
      return tmp;
  return NULL;
} /* find */

void dohitta(Post *first){
  char vem[20];
  Post *tmp;
  printf("Vem: ");
  fgets(vem, 20, stdin);
  *strchr(vem,'\n')='\0';
  if (tmp=find(first, strtoupper(vem)))
    printf("%d\t%s\n", tmp->nr, tmp->data);
  else
    printf("Ingen sådan!\n");
} /* dohitta */

int main(void){
  Post *list=makelist();
  char kom;
  printf("Du kan ge följande kommandon:\n"
	 " A - för att skriva ut alla (ej implementerad än!)\n"
	 " H - för att hitta en viss\n"
	 " Q - för att avsluta\n");
  for(;;){
    printf("Kommando> ");
    kom=getchar();
    while (getchar()!='\n')
      ;
    switch(toupper(kom)){
    case 'A': printf("Ej implementerad än!\n"); break;
    case 'H': dohitta(list); break;
    case 'Q': exit(0);
    default: fprintf(stderr, "Felaktigt kommando %c!\n", kom);
    } /* switch */
  } /* for */
} /* main */
