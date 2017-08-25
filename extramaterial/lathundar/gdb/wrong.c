/* Demoprogram för gdb-presenation *:58 HT07     */
/* Detta program är behäftat med ett antal fel   */
/* för att kunna användas vid presentation av    */
/* GNUs avlusnings-(debuggings-)verktyg gdb      */ 

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
    str[i]=(i==5)?'X':toupper(str[i]); /* Avsiktligt fel (långsökt) */
  return str;
} /* strtoupper */

Post *makelist(void){
  Post *first=NULL, *last=NULL, *ny=NULL;
  int i;
  for(i=0; i<antal; i++){
    /* ny=malloc(sizeof(Post));  */ /* Avsiktligt fel */
    ny->nr=i;
    /* ny->data=malloc(strlen(strings[i]+1)); */  /* Avsiktligt fel */
    strcpy(ny->data, strings[i]);
    if (first==NULL) last=first=ny;
    else last=last->next=ny;
  } /* for */
  return first;
} /* makelist */

void printlist(Post *first){
  Post *tmp;
  for(tmp=first; tmp!=NULL; tmp=tmp->next)
    printf("%d\t%s\n", tmp->nr, tmp->data);
} /* printlist */

Post *find(Post *first, char *str){
  Post *tmp;
  for(tmp=first; tmp!=NULL; tmp->next)       /* Avsiktligt fel */
    if (strcmp(tmp->data, str)==0)
      return tmp;
  return NULL;
} /* find */

void dohitta(Post *first){
  char vem[20];
  Post *tmp;
  printf("Vem: ");
  fgets(vem, 20, stdin);
  /* *strchr(vem, '\n')='\0'; */      /* Avsiktligt fel */
  if ((tmp=find(first, strtoupper(vem))))
    printf("%d\t%s\n", tmp->nr, tmp->data);
  else
    printf("Ingen sådan!\n");
} /* dohitta */

int main(void){
  Post *list=makelist();
  char kom;
  printf("Du kan ge följande kommandon:\n"
	 " A - för att skriva ut alla\n"
	 " H - för att hitta en viss\n"
	 " Q - för att avsluta\n");
  for(;;){
    printf("Kommando> ");
    kom=getchar();
    while (getchar()!='\n')
      ;
    switch(toupper(kom)){
    case 'A': printlist(list); break;
    case 'H': dohitta(list); break;
    case 'Q': exit(0);
    default: fprintf(stderr, "Felaktigt kommando %c!\n", kom);
    } /* switch */
  } /* for */
} /* main */
