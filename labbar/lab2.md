# Labb 2: I/O och funktioner

## Varningar

Från och med den här labben kommer vi att använda flaggan `-Wall`
(`W`arnings `all`) varje gång vi kompilerar. Det berättar för
kompilatorn att den ska ge varningar för fler saker än vanligt.
Var vaksam om du får en varning från kompilatorn. Även om felet
inte alltid ligger precis där kompilatorn varnar så betyder en
varning att någonting är fel i programmet, eller borde skrivas
om. Om man tar för vana att inte fixa "ofarliga varningar" kommer
det att vara svårare att hitta "de farliga varningarna" i allt
mummel som kompilatorn spottar ur sig. 


**Åtgärda alltid varningar innan du går vidare**

## Debugging

Ingen människa skriver felfria program direkt. Ibland kan ett
program kompilera men ändå göra fel eller krascha, och det är inte
alltid lätt att hitta vad som orsakar en bugg. Ett verktyg som kan
användas för att hitta buggar i ett körande program kallas för en
"debugger" (på stolpig svenska kallas de ibland för "avlusare").
Program skrivna i C kan "debuggas" med programmet `gdb` (eller
`lldb` om du kör på OS X).

I kursrepots [extramaterial](../extramaterial) finns en en kort
screencast om `gdb` som du bör se vid tillfälle, samt en lathund
som går igenom hur `gdb` fungerar. Om du stöter på en bugg och
vill prova att använda `gdb` redan på den här labben kan du be en
assistent om hjälp.


## Uppvärmning: Fizz Buzz

Fizz Buzz är en klassisk programmeringsövning som går ut på att
implementera leken "Fizz Buzz" där man sitter i en ring och räknar
uppåt från 1. Den som börjar börjar säger 1, och nästa person
säger 2, etc. -- men alla tal som är delbara med 3 ersätts med
"Fizz", alla tal som är delbara med 5 ersätts med "Buzz" och alla
tal som är delbara med både 3 och 5 med "Fizz Buzz".

Skriv ett program som räknar från 1 till ett på kommandoraden
angivet tal på detta sätt:

    > gcc -Wall fizzbuzz.c
    > ./a.out 16
    1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, Fizz Buzz, 16
    > _

Strukturera programmet så här:

1. En `main()`-funktion som läser in ett tal _T_ som ett kommandoradsargument (se föregående labb)
2. En loop i `main()`-funktionen som räknar från 1 till _T_
3. En funktion `void print_number(int num)` som anropas för varje _T_ och skriver _T_, Fizz, Buzz eller Fizz Buzz
4. Fundera på hur du skall göra för att inte ha något sista avslutande `,`-tecken

**Tips:** i C är operatorn `%` modulo, dvs. `10 % 5 = 0` och `10 % 3 = 1`.


## I/O

I/O -- input/output är en viktig del av många program, och ibland
knepigt beroende på hur långt ned i mjukvarustacken man befinner
sig. Ju närmare hårdvaran -- desto lägre abstraktionsnivå erbjuds,
vilket tvingar oss att tänka på fler detaljer.

Vi skall börja med att implementera en generell rutin för att
ställa en fråga och läsa in ett svar i form av ett heltal. Vi
kommer att göra det i ett antal delsteg som förbättrar programmet
på ett antal sätt, och därigenom illustrera en vanlig
programmeringsprocess.

Börja med att skapa filen `ioopm/lab2/utils.c` -- vi skall jobba
med den idag. Den skall inkludera `stdio.h`, som är C:s
standardbibliotek för I/O-funktioner.


### Del 1: `ask_question_int()`

Tillägg i `utils.c`.

Funktionen `scanf()` fungerar analogt med `printf()` men för
_inläsning_ av data, inte utskrift. Följande två rader visar
hur man kan deklarera en heltalsvariabel `result` och sedan
läsa in ett heltal från terminalen och spara i variabeln:

```c
int result;
scanf("%d", &result);
```

Observera `&`-tecknet före `result` ovan! Det är den så-kallade
**adresstagningsoperatorn** som returnerar _adressen_ till en plats
i minnet. Alltså, `result` är en `int` (enligt vår deklaration)
men `&result` har typen `int *` vilket betyder _adressen till en
plats i minnet där det finns en int_. Detta är en så-kallad
pekare, och vi skall få anledning att återkomma till pekare
tusentals gånger under kursen. Nu räcker det med att veta att alla
anrop till `scanf()` måste innehålla adresser till platser i
minnet där resultaten av en inläsning skall läggas. Om vi t.ex.
vill läsa in tre tal:

```c
int first;
int second;
int third;
scanf("%d %d %d", &first, &second, &third);
```

Funktionen `scanf()` har väldigt många olika möjligheter och
"features" som vi inte hinner gå in på här -- vi uppmuntrar att du
bläddrar genom manualsidan för `scanf()` och dess syskonfunktioner
för att bilda dig en uppfattning (`man scanf`, men inte under
labben).

Nu kan vi skriva en funktion `ask_question_int()` som tar en
sträng (`char *`) som indata, skriver ut strängen på terminalen,
läser in ett heltal, och returnerar det. _Signaturen_ för
`ask_question_int()` skall följaktigen vara:

```c
int ask_question_int(char *question)
```

(Strikt sett är `question` inte en del av signaturen -- det är bara
ett internt namn på det inskickade argumentet och kan fritt döpas
om utan att det påverkar användare av funktionen.)

Vi är nu redo att skriva vår första implementation av funktionen.

**OBS:** innan det finns en `main()`-funktion i denna fil måste du
kompilera med flaggan `-c` för att tala om för kompilatorn att du
inte försöker skapa ett körbart program. Vi återkommer till denna
flagga senare under kursen. (Du kan också lägga till en
`main()`-funktion som vi gör nedan.)

```c
int ask_question_int(char *question)
{
  printf("%s\n", question);
  int result = -1; // godtyckligt valt nummer
  scanf("%d", &result);
  return result;
}
```

För enkelhets skull lägger vi till en `main()`-funktion som kan
testa vårt program. Senare kommer vi att ta bort den. Syftet med
`utils.c` är nämligen att vi skall skapa några grundläggande
funktioner i ett **bibliotek** som kommer att återanvändas i
inlämningsuppgifterna senare.

```c
int main(void)
{
  int tal;

  tal = ask_question_int("Första talet:");
  printf("Du skrev '%d'\n", tal);

  tal = ask_question_int("Andra talet:");
  printf("Du skrev '%d'\n", tal);

  return 0;
}
```

Kompilera och kör programmet! Testa med följande input och notera
vad resultatet blir:

* `1` och `1`
* `1a` och `1`
* `1` och `1a`
* `a` och `42`

Inläsning från tangentbordet i C fungerar genom en
_tangentbordsbuffert_ som du kan tänka på som en sträng i datorns
minne. `scanf()`-funktionen ovan förväntar sig ett heltal
(styrkoden `%d` -- tänk _digits_) vilket betyder att inläsningen
av `1a` slutar vid `1`, så att `a\n` lämnas kvar i minnet
(observera radbrytningstecknet `\n`). Vid nästa inläsning finns
`a\n` kvar i bufferten och eftersom `scanf()` läser rad för rad
kommer scanf inte att kunna läsa in något tal.

Vår `ask_question_int()` behöver bli lite smartare: vi måste
kontrollera vad `scanf()` lyckas med.

Returvärdet från `scanf()` är så många inläsningar som `scanf()`
lyckades med. I vårt fall försöker vi bara göra en (en styrkod
`%d`) så om `scanf()` returnerar `1` vet vi att inläsningen är
lyckad.

Intuitivt kanske man kan tycka att följande funktion borde lösa
problemet:

:warning: **OBS!** _Inte dålig kod, men inte rätt för vad vi vill nu._ :warning: 
```c
int ask_question_int(char *question)
{

  int result = -1;

  do
  {
    printf("%s\n", question);
  }
  while (scanf("%d", &result) != 1);

  return result;
}
```

Det gör den inte, och problemet ligger i att en misslyckad
`scanf()` inte tömmer tangentbordsbufferten (vi har ju bara bett
om att läsa till och med nästa tal -- inte det som kommer efter).
Nästa varv i loopen i detta program är alltså dömt att misslyckas.
Det betyder att om vi skriver in `1a` med detta program kommer
programmet att köra för evigt!

Det finns ingen bästa lösning på detta problem, men en möjlig
lösning som är både vettig och enkel är att kasta bort resten av
den inlästa raden. Dvs. om du skriver in `1a...`, läses `1` in,
och `a...` kastas bort oavsett vad som är i `...`.

Vi kan tömma tangentbordets buffer så här:

```c
int c;
do
{
  c = getchar();
}
while (c != '\n');
```

Denna loop tar tecken från terminalen, ett efter ett, tills den
läser ett `\n`. På så vis töms tangentbordets buffert. Vi kan nu
skriva en fungerande `ask_question_int()`:

```c
int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n');
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}
```

**Not**

Ändra gärna `while (c != '\n');` till `while (c != '\n' && c != EOF);`.
Den andra villkoret betyder att `c` inte skall vara specialtecknet
som avser att en fil är slut -- End Of File. Det hanterar inmatning
som avslutas utan att det kommer en ny rad sist.

**Tips** Funktionen blir enklare att läsa och förstå om du flyttar
ut den inre loopen (den som tömmer tangentbordets buffert) till en
egen funktion med ett bra namn, till exempel
`clear_input_buffer()`.


### Del 2: Inläsning av en sträng

Tillägg i `utils.c`.

Vi har nu sett ett exempel på inläsning av ett heltal. Låt oss nu
läsa in en sträng istället. Vi skall skriva
`ask_question_string()` med motsvarande beteende -- men denna gång
skall vi inte tillåta den tomma strängen. Något som gör denna
funktion mycket svårare att skriva är att strängar inte har en fix
storlek. Om vi skall använda `scanf()` för att läsa in en sträng
måste vi skicka med adressen till en plats i minnet där resultatet
skall sparas, analogt med inläsning av heltal. Ett klassiskt
säkerhetshål i C är s.k. "buffer exploits" som i stort går ut på
att mata in för långa strängar i ett program så att de inte
ryms i buffrarna och spiller över in i programmets övriga minne.
Ta därför alltid för vana när du läser in data i ett C-program att
enbart använda funktioner som låter dig ange hur många tecken som
ryms på den plats där det inlästa datat skall sparas!

Här är en **regelvidrig** (och dessutom **felaktig** -- testa
själv) inläsningsfunktion som absolut aldrig får användas. Här
använder vi en array med 255 tecken som inläsningsbuffert (vi har
alltså plats för 254 tecken + null-tecknet), och använder oss av
två hjälpfunktioner för att kontrollera strängens längd
(`strlen()`) och skapa en kopia av den inlästa strängen som vi
returnerar (`strdup()`):

:warning: **OBS!** _Varning för negativt exempel -- nedanstående kod är dålig._ :warning: 
```c
#include <string.h>

char *ask_question_string(char *question)
{

  char result[255]; // <-- bufferstorlek 255
  do
    {
      printf("%s\n", question);
      scanf("%s", result); // <-- scanf vet ej bufferstorlek! (inläsning av >254 tecken möjligt!)
    }
  while (strlen(result) > 0);
  return strdup(result);
}
```

**Nu skall du skriva en funktion** som tar emot en buffert (i form av
en sträng, `char *`), en storleksangivelse för bufferten i form av
ett heltal och som läser in en sträng i bufferten. Det avslutande
`'\n'`-tecknet skall _inte_ vara med i strängen som returneras.
Funktionens signatur skall vara:

```c
int read_string(char *buf, int buf_siz)
```

Där returvärdet är antalet inlästa tecken, alltså hur många av de
`buf_siz` tecknen i `buf` som faktiskt används, förutom
null-tecknet. Valida värden är alltså `[0..buf_siz-1]`.

Att läsa in en sträng är väldigt likt att tömma
tangentbordsbufferten som vi gjorde ovan, med den lilla skillnaden
att vi sparar det vi läste in i `buf`. Vidare måste vi:

1. Lägga till en räknare för hur många tecken vi läst in
2. Se till att räknarens värde inte överstiger `buf_siz-1`
3. Se till att strängen vi läser in blir korrekt nullterminerad

Som du kanske minns från föregående labb är en sträng en array av
tecken som slutar med tecknet `'\0'`. Eftersom detta tecken också
tar upp en plats i strängen får vi inte läsa in `buf_siz` tecken
utan högst `buf_siz-1` tecken. Genom att skriva `'\0'` sist i
strängen har vi markerat dess slut. Alltså: om vi har läst in 5
tecken i en buffert `buf` skall vi sätta `buf[5] = '\0';` dvs.
skriva `'\0'` på den sjätte platsen i `buf`. Om `buf` endast
hade längden `5` hade vi fått sluta läsa in efter 4 tecken så
att vi kunde göra `buf[4] = '\0'`.

Om vi lyckas läsa hela vägen till det sista `'\n'`-tecknet behöver
vi inte tömma tangentbordets buffer. Om vår inläsningsbuffer tar
slut först, dock, så skall vi tömma tangentbordets buffer på samma
sätt om vi gjorde i `ask_question_int()`.

Här är en enkel `main()`-funktion som du kan använda för att
testa ditt program:

```c
int main(void)
{
    int buf_siz = 255;
    int read = 0;
    char buf[buf_siz];

    puts("Läs in en sträng:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    puts("Läs in en sträng till:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    return 0;
}
```

Notera att `read_string()` inte returnerar den inlästa strängen --
genom att `main()`-funktionen delat adressen till `buf`-arrayen
med `read_string()` kan den senare skicka data tillbaka till den
förra genom att skriva i arrayen.

Pröva med långa strängar, korta strängar, med och utan mellanslag,
en lång följd av en kort, en kort följd av en lång, etc. Notera
att första varje anrop till `read_string()` använder samma
buffert, dvs. den andra inläsningen skriver över innehållet som
var inläst av den första inläsningen. Detta är i sig inget
problem, men kan kanske hjälpa dig att förstå varför du kan få
rester av gammal input i din sträng om du gör fel.


### Del 3: `ask_question_string()`

Tillägg i `utils.c`.

Nu när vi har en `read_string()`-funktion är det enkelt att
implementera en `ask_question_string()`. Gör det, och använd
returvärdet från `read_string()` för att fånga tomma strängen
(vars längd är 0) och i så fall upprepa frågan på samma sätt som
`ask_question_int()`.

Funktionen `ask_question_string()` går i stort sett att extrahera
från det första försöket att implementera `ask_question_string()`
men skall ha signaturen:

```c
char *ask_question_string(char *question, char *buf, int buf_siz)
```

Senare under kursen skall vi se hur vi kan ändra så att signaturen
för funktionen blir

```c
char *ask_question_string(char *question)
```

genom att skapa ett dynamiskt allokerat minnesutrymme i vilket vi
kan spara den inlästa strängen.


## Gör om `utils.c` till ett riktigt bibliotek

Nu skall vi skapa vår första **header-fil**! Skapa `utils.h` i
samma katalog som `utils.c` och _flytta_ dit samtliga
funktionsprototyper från `utils.c`. I `utils.h` borde det nu alltså
åtminstone stå:

```c
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
int ask_question_int(char *question);
char *ask_question_string(char *question, char *buf, int buf_siz);
```

Som första rader i `utils.h` skriv

```c
#ifndef __UTILS_H__
#define __UTILS_H__
```

och som sista rader skriv

```c
#endif
```

Vi återkommer till dessa magiska instruktioner senare. Om du är
nyfiken -- kolla i kurslitteraturen, sök på nätet, eller fråga en
assistent!

Lägg till `#include "utils.h"` i `utils.c` -- notera `"` istället för `<`.

Passa också på att ta bort `main()`-funktione ur `utils.c`. Nu har vi
ett "riktigt bibliotek" som kan inkluderas av program som behöver komma
åt hjälpfunktionerna.


## *Applikation: Gissa talet (Skall redovisas)

Nu skall vi skapa programmet `guess.c` som använder sig av våra
två `ask_`-funktioner. Interaktion med programmet skall se ut så här:

    > gcc -Wall guess.c
    > ./a.out
    Skriv in ditt namn:
    Tobias
    Du Tobias, jag tänker på ett tal ... kan du gissa vilket?
    0
    För litet!
    1000
    För stort!
    500!
    För stort!
    ... (osv)
    För litet!
    42
    Bingo!
    Det tog Tobias 12 gissningar att komma fram till 42
    > _

Om man tar mer än 15 gissningar på sig skall programmet skriva ut:

    ...
    Nu har du slut på gissningar! Jag tänkte på 42!
    > _

Programmet skall alltså:

1. Slumpa fram ett tal _T_ (med hjälp av funktionen `random()` i `stdlib.h`)
2. Fråga efter användarens namn _N_
3. Skriva ut "Du _N_, jag tänker på ett tal kan du gissa vilket?"
4. I en loop, läsa in tal från användaren och skriva ut "För litet!"
   eller "För stort!" eller "Bingo!"
5. Vid bingo, skriv ut "Det tog _N_ _G_ gissningar att komma fram till _T_"
6. Om _G_ når 15, skriva ut "Nu har du slut på gissningar! Jag tänkte på _T_!"

:warning: **OBS!** _På vissa maskiner fungerar rand() bättre än random()._ :warning:

Funktionen `random()` i `stdlib.h` returnerar ett slumptal som kan vara mycket
stort. För att skapa ett slumptal mellan 0 och _N_ kan du använda
_modulo_:

```c
random() % 1024  // slumptal mellan 0 och 1023
```

Programmet använder naturligtvis funktionerna från `utils.c`, utefter
den beskrivning som finns i `utils.h`. Importera dem
i `guess.c` så här:

```c
#include "utils.h"
```

Om när du kompilerar -- ange båda källkodsfilerna:

    > gcc -Wall utils.c guess.c

Om du har glömt att ta bort `main()`-funktionen från `utils.c`
kommer detta inte att fungera eftersom det då finns två
`main()`-funktioner, vilket är tvetydigt och därför inte är
tillåtet!


# Extrauppgifter

För dig som är tidigt färdig eller känner att du vill arbeta mer
med materialet.

## Implementera om `ask_question_int()`

Implementera om `ask_question_int()` i termer av `read_string()`
och den `is_number()` som du implementerade på föregående labb.

Du skall alltså använda `read_string()` för att läsa in en sträng,
och sedan `is_number()` för att verifiera att den inlästa strängen
faktiskt är ett tal.

Om du lägger till `is_number()` i `utils.c` har du utökat ditt
utility-bibliotek!


## Implementera `ask_question_float()`

Implementera funktione `ask_question_float()` i termer av
`read_string()` och en `is_float()` som du själv måste skriva. Du
kan utgå från `is_number()` men också tillåta förelkomsten av
**en** punkt `.` någonstans i strängen. Funktionen `atof()` i
`ctype.h` vet hur man omvandlar en sträng till ett flyttal.


## Enkel aritmetikdrillare

Skriv ett enkelt program som ett enkelt artitmetiskt uttryck på
formatet

    tal1 op tal2 = ?

Där `tal1` och `tal2` är framslumpade tal i intervallet [1..1024]
och `op` är en framslumpad operator i mängden {+, -, *, /}.

Användaren skall mata in tal och programmet kontrollerar att det
inmatade talet är korrekt.

En rolig utökning av denna uppgift är att tillåta att användaren
svarar `fyrahundratjugosju` istället för `427`. Du kan
implementera detta på två sätt:

1. implementera en funktion som konverterar heltal till dess
   textuella motsvarighet. Du kan sedan använda funktionen
   `strcmp()` från `string.h` för att göra jämförelsen.
2. implementera en funktion som konverterar från ett heltals
   textuella motsvarighet till heltalet, dvs. från `två` till `2`.
   Du kan nu använda `==`-operatorn för att göra jämförelsen.

Notera att `strcmp()`-funktionen tar emot två strängar och
returnerar 0 om de är lika. Dvs.:

```c
char *str1 = "foo";
char *str2 = "bar";
if (strcmp(str1, str2) == 0)
{
  puts("Strängarna är lika");
}
else
{
  puts("Strängarna är inte lika");
}
```
