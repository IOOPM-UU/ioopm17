# Labb 3: Rekursion, Generalisering & Funktionspekare

Om du känner att du är stressad och har ont om tid -- kan det
ibland vara en god idé att pröva att gå direkt på funktionspekare,
dvs. hoppa över början.


## Uppvärmning: strängfunktioner

Skapa ett program `str.c`.

Som du säkert minns är C:s strängtyp `char *`. Det betyder en
adress till en plats i minnet där det finns lagrat **ett eller
fler tecken**. Det är i de flesta avseenden ekvivalent med typen
`char []` som avser en array av ett eller fler tecken. Strängar
innehåller ingen information om hur långa de är -- istället
används ett speciellt tecken som ett stopptecken: det s.k.
null-tecknet som skrivs `'\0'`.

Om vi skriver `char *str = "Guy Maddin, Winnipeg";` har vi skapat
en sträng vars innehåll är 21 tecken. Om vi skriver detta som en
array: `['G', 'u', 'y', ' ', 'M', 'a', 'd', 'd', 'i', 'n', ',', ' ', 'W', 'i', 'n', 'n', 'i', 'p', 'e', 'g', '\0']`. Det enda sättet att ta reda på hur lång
en sträng är är att "loopa igenom den" och leta efter null-tecknet.


### Uppvärmningsuppgift 1: implementera en egen `strlen()`-motsvarighet

Implementera en funktion `string_length()` som tar som argument en
sträng och returnerar ett heltal som avser hur många tecken som
var i strängen. Du kan t.ex. använda en loop och en
heltalsvariabel som räknare för att lösa uppgiften. För varje varv
i loopen, gå ett steg längre "till höger" i arrayen, och leta
efter ett `'\0'`-tecken. Antalet gångna steg är strängens längd.

Testa ditt program genom att jämföra dess output med `strlen()`
som finns i `string.h`. Du kan t.ex. skriva så här:

```c
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s words or string", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      int expected = strlen(argv[i]);
      int actual   = string_length(argv[i]);
      printf("strlen(\"%s\")=%d\t\tstring_length(\"%s\")=%d\n",
             argv[i], expected, argv[i], actual);
    }
  }
  return 0;
}
```

Observera att för att skriva ut `"` inuti en sträng så måste vi
"escape:a dem", dvs. skriva dem som `\"`. Tecknet `\t` står för
tab.

Exempelkörning:

    > gcc -Wall str.c
    > ./a.out hej hopp
    strlen("hej")=3    string_length("hej")=3
    strlen("hopp")=4   string_length("hopp")=4
    >

Ovan kan vi se att `strlen()` och `string_length()` ger samma svar
för de ord vi skickade in vilket ger förhoppning om att
`string_length()` är korrekt implementerad.


### Uppvärmningsuppgift 2: implementera egna enkla print-satser

Analogt med hur vi har använt funktionen `getchar()` för att läsa
in tecken för tecken kan vi använda funktionen `putchar()` för att
skriva tecken för tecken. Om jag t.ex. har en sträng `s` kan jag
skriva `putchar(s[3])` för att skriva ut dess fjärde tecken.

1. Implementera funktionen `print()` som tar en sträng och skriver
   ut den på terminalen (med hjälp av `putchar()`) fast **utan**
   avslutande radbrytning.
2. Implementera `println()` -- en egen motsvarighet till `puts()`,
   som tar en sträng och skriver ut den på terminalen (med hjälp
   av `print()`) **med** en avslutande radbrytning. Jämför med
   `puts()` i ditt program för att kontrollera att du gör rätt.
3. Lägg till `print()` och `println()` i `utils`-biblioteket!



## Rekursion i C

Du är bekant med rekursionsbegreppet sedan PKD. Rekursion i C
fungerar i stort sett likadant. I labb 1 var en extrauppgift att implementera ett
program som skrev ut tal ur Fibonacci-serien på ett _imperativt_
sätt. Nedan följer ett liknande program, som bara skriver ut det
sista talet i serien och inte varenda tal på vägen dit. Målet med
denna uppgift är att skriva om `fib()`-funktionen så att den blir
_rekursiv_. Efter koden nedan kommer ett exempel som visar hur man
kan skriva en annan imperativ funktion med rekursion.

```c
#include <stdio.h>
#include <stdlib.h>

/// Den intressanta delen av programmet
int fib(int num)
{
  int ppf = 0; // the two given fib values
  int pf  = 1;

  for (int i = 0; i < num; ++i)
  {
    int tmp = pf;
    pf = ppf + pf;
    ppf = tmp;
  }

  return pf;
}

/// Den ointressanta main()-funktionen
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    int n = atoi(argv[1]);
    if (n < 2)
    {
      printf("fib(%d) = %d\n", n, n);
    }
    else
    {
      printf("fib(%s) = %d\n", argv[1], fib(n));
    }
  }
  return 0;
}
```

### Exempel på iteration ==> rekursion: sum

Nedanstående funktion tar in en array av heltal samt längden på
arrayen och adderar talen i arrayen och returnerar summan.

```c
long sum(int numbers[], int numbers_siz)
{
  long result = 0;

  for (int i = 0; i < number_siz; ++i)
  {
    result += numbers[i];
  }

  return result;
}
```

En rekursiv motsvarighet kan skrivas utifrån insikten att summan
av en serie av N tal är lika med det första talet + summan av
resterande tal. Alltså, om vi vill beräkna `sum([1, 2, 3, 4])`
så kan vi räkna ut den som `1 + sum([2, 3, 4])`, och så vidare,
där basfallet är `sum([]) = 0`, alltså summan av alla tal i en
tom array är 0.

Så här skulle vi kunna skriva C-kod som fungerar på detta sätt:

```c
long rec_sum(int numbers[], int numbers_siz, int index)
{
  if (index < numbers_siz)
  {
    return numbers[index] + rec_sum(numbers, numbers_siz, index + 1);
  }
  else
  {
    return 0;
  }
}
```

Om vi använder `rec_sum` för att summera arrayen `[1, 2, 3]`
kommer vi att göra följande steg (förenklat):

1. `rec_sum([1, 2, 3]) = return 1 + rec_sum([2, 3])`
2. `rec_sum([2, 3])    = return 2 + rec_sum([3])`
3. `rec_sum([3])       = return 3 + rec_sum([])`
4. `rec_sum([])        = return 0`

Vid (4) har vi nått slutet av vår rekursion och vi kan "gå tillbaka"
och räkna ut att svaret på (3) är `3 + 0` och därmed blir svaret på
(2) `2 + 3 + 0` och (1) `1 + 2 + 3 + 0`. Som man kunde förvänta sig.

Eftersom vi inte kan "skala av element från arrayen" använder vi
en extra parameter `index` som stiger tills den når `numbers_siz`.
Varje rekursionssteg har alltså tillgång till hela arrayen men
börjar titta från `index`. Vid startanropet skall `index` vara 0.
Vi kan nu implementera `sum()` i termer av `rec_sum()`:

```c
long sum(int numbers[], int numbers_siz)
{
  return rec_sum(numbers, numbers_siz, 0);
}
```

**Nu återgår vi till uppgiften**: skriv om `fib()`-funktionen i
programmet längst upp på sidan så att den är **rekursiv**.

**Ledning:**
Vi upprepar den rekursiva definitionen av Fibonacci-serien från labb 1:

    fib(1) = 1
    fib(2) = 1
    fib(i) = fib(i-1) + fib(i-2) om i > 2

En något mer C-lik pseudokod skulle vara:

    fib(i) = 1                     om i = 0
             1                     om i = 1
             fib(i-1) + fib(i-2)   annars

Senare under kursen skall vi diskutera problemet med ändligt
utrymme på stacken och djup rekursion. Ett anrop till `rec_sum()`
med en väldigt stor array kommer sannolikt att krascha programmet
om inte kompilatorn är smart nog att översätta rekursionen till
en loop -- mer om detta senare alltså.

**Testa** att ditt program är korrekt genom att jämföra dess resultat
med resultatet från ditt imperativa program.

## Funktionspekare

Pekare är som bekant adresser till platser i datorns minne där
data finns lagrat. Vi har ännu inte stiftat någon djup bekantskap
med dem men vi har sett att strängar i C är pekare (`char *`), och
att vi skickat in pekare till `int`:ar i `scanf()`. Nu skall vi
stifta bekantskap med pekare till _funktioner_. Detta motsvarar
högre ordningens funktioner som du använt i Haskell, t.ex. när du
skickat in en funktion och en datasamling till `map`.

C:s syntax för funktionspekares typer är fruktansvärd och det är
därför brukligt att man skapa ett _typalias_ -- dvs. skapar ett
beskrivande namn på en krånglig typ som man sedan kan använda
istället för dess krångliga motsvarighet. Syntaxen för ett
typalias är så här:

    typedef existerande_typ nytt_namn;

Exempel på typalias som inte berör funktionspekare:

:warning: **OBS!** _se noten om `string_t` nedan!_ :warning:
```c
typedef char * string_t;
typedef unsigned int age_t;
```

Här har vi skapat två typalias: `string_t` kan nu användas överallt
som en synonym för `char *` och vi har angivit att typen `age_t` är
ett icke-negativt heltal. Suffixet `_t` är en namnkonvention.

Just typaliaset `string_t` är ett alias vi skall undvika eftersom
det avviker från alla andra C-program och därför blir förvirrande
för någon som läser din kod, även om `string_t` förmodligen har
mindre kognitiv belastning än `char *` för en ny C-programmerare.

Låt oss nu använda `typedef`-nyckelordet för att definiera ett
typalias för en funktion. Det är invecklat, men inte speciellt
svårt när man väl har lärt sig läsa koden:

```c
typedef int(*int_fold_func)(int, int);
```

Koden ovan definierar typen `int_fold_func` som en funktion som
tar som argument två `int`:ar och returnerar en `int`. I Haskell
skulle typen skrivas `Int -> Int -> Int`. Asterisken `*` framför
namnet `int_fold_func` ovan är det som gör det hela till en
pekare. **Denna skall dock inte vara med i namnet**.

Om jag har en funktion `add(...)` och vill skicka en pekare till
den funktionen skriver jag alltså `add`. Funktionens namn utan
parenteser och argument. Om jag skriver `add(2,2)` är det ju
ett helt vanligt **anrop** till funktionen och det som skickas
in är resultatet!

Nu kan vi använda `int_fold_func` som en datatyp och deklarara
t.ex. en "[left fold](http://learnyouahaskell.com/higher-order-functions)" (som du kanske minns från PKD). Om du inte minns hur en left fold fungerar -- försök
att räkna ut det från C-koden nedan!

```c
/// En funktion som tar en array av heltal, arrayens längd och
/// en pekare till en funktion f av typen Int -> Int -> Int
int foldl_int_int(int numbers[], int numbers_siz, int_fold_func f)
{
  int result = 0;

  // Loopa över arrayen och för varje element e utför result = f(result, e)
  for (int i = 0; i < numbers_siz; ++i)
  {
    result = f(result, numbers[i]);
  }

  return result;
}
```

Låt oss skriva en funktion som adderar två tal:

```c
int add(int a, int b)
{
  return a + b;
}
```

Eftersom `add()` är en funktion av typen `Int -> Int -> Int` kan
den användas tillsammans med `foldl_int_int`. För att skicka med
en funktion som en parameter skriver du bara funktionens namn, i
detta fall alltså `add`.

**Uppgift:** Skriv om `sum()`-funktionen ovan med hjälp av
`foldl_int_int()` och `add()`. Du behöver inte ändra i vare sig
`foldl_int_int()` eller `add()`.


## Generell inläsningsrutin

Skapa en ny fil med ett lämpligt namn, t.ex. `experiment.c` med
en tom `main()`-funktion. Skriv all kod för denna uppgift här,
kompilera ofta och fundera på hur du kan skriva kod i
`main()`-funktionen som testar/kör den kod som du skriver.
Vi kommer att vilja använda kod som du har skrivit tidigare.
Välj själv om du vill inkludera `utils.h` och kompilera med
`gcc experiment.c utils.c` eller om du vill kopiera in all
kod som behövs i `experiment.c`.

Med hjälp av funktionspekare skall vi nu skriva en generell
inläsningsrutin som ger ytterligare abstraktion vid inläsning. Den
fångar det generella mönstret för inläsning:

1. Skriv ut frågan (t.ex. "mata in ett tal")
2. Läser in svaret
3. Kontrollerar att svaret är på rätt format (t.ex. att det är ett tal) och går tillbaka till 1. igen vid behov
4. Konverterar det till rätt format (t.ex. från `"42"` till `42`)
5. Returnerar resultatet

För att göra detta skall vår nya `ask_question()`-funktion ha tre
parametrar:

1. Frågan i form av en sträng (`char *`)
2. En pekare till en funktion som kontrollerar att svaret har rätt format
3. En pekare till en funktion som konverterar en sträng till något annat format

Typen på kontrollfunktionen skall vara `char * -> bool`, dvs. den tar emot
en sträng och returnerar sant eller falskt.

Typen på konverteringsfunktionen skall vara `char * -> answer_t` --
vilket introducerar en ny typ som vi ännu inte har sätt, nämligen
typen `answer_t` som är en s.k. **union**:

```c
typedef union {
  int   i;
  float f;
  char *s;
} answer_t;
```

Typen `answer_t` avser ett värde som _antingen_ är en `int` _eller_
en `float` _eller_ en sträng (`char *`). Om `val` är en variabel av
typen `answer_t` så kan jag tilldela den ett heltal via `val.i =
42` och läsa det på motsvarande sätt `... = val.i`, eller en
sträng via `val.s = ...` och `... = val.s`. Namnen `i`, `f` och `s`
har jag valt i min definition av `answer_t` och kan bytas ut mot
andra namn om man så önskar.

**Uppgift!** Använd `typedef` för att definiera typerna
`check_func` och `convert_func` med typerna ovan. Utgå från
exemplet från `int_fold_func`.

Ett exempel på en kontrollfunktion är den `is_number()` som du
redan skrivit (labb 1) och som tar in en sträng och returnerar true eller
false beroende på om strängen kan konverteras till ett tal. En
kontrollfunktion som kontrollerar att en sträng inte är tom kan se
ut så här:

```c
/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  if (strlen(str) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
```

Eller, mer kompakt och bättre:

```c
/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  return strlen(str) > 0;
}
```

Ett exempel på en funktion som går att använda som
konverteringsfunktion är funktionen `atoi()` som vi har använt
förut. Den fungerar eftersom `atoi()` returnerar ett heltal som så
att säga är en delmängd av `answer_t`.

Dock: Om man försöker skicka in `atoi` som argument till en
funktion vars motsvarande parameter är `convert_func` kommer
kompilatorn att klaga eftersom `answer_t` och `int` inte är samma
typ. Det kan man lösa med hjälp av en **typomvandling** (eng. type
cast):

```c
atoi                     // har typen char * -> int
(convert_func) atoi      // har typen char * -> answer_t
```

**Uppgift!** Nu är det dags att skriva funktionen `ask_question()`
med signaturen:

```c
answer_t ask_question(char *question, check_func check, convert_func convert)
```

Inuti denna funktion avser variablerna `check` och `convert`
funktioner som kan anropas `check(str)` etc.

1. Skapa en buffert av lämplig längd
2. I en loop
   - skriv ut frågan
   - läs in en sträng med din egen `read_string()`-funktion
   - Använd `check` för att kontrollera att det du läst in är korrekt och terminera loopen
3. Använd `convert` för att konvertera resultatet och returnera det

Med hjälp av din generella `ask_question()`-funktion är det nu busenkelt
att definiera nya. T.ex. kan vi definiera `ask_question_int()` så här:

```c
int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i; // svaret som ett heltal
}
```

Om du har skrivit en `is_float()` på en tidigare labb kan du
använda den för att definiera `ask_question_float()`. Dock -- för
att göra detta måste vi skapa en funktion som skapar ett
`answer_t` från en `double`:

```c
answer_t make_float(char *str)
{
  answer_t a;      // skapa ett oinitierat answer_t-värde
  a.f = atof(str); // gör det till en float, via atof
  return a;        // returnera värdet
}
```

Eller, mer kompakt (skapar ett nytt `answer_t`-värde) -- via en syntax
som vi skall behandla i mer detalj på nästa labb:

```c
answer_t make_float(char *str)
{
  return (answer_t) { .f = atof(str) };
}
```

Här skriver vi `ask_question_float()` utan den onödiga variabeln
`answer` bara för att visa att det också är möjligt (notera `.f`
på slutet!).

```c
double ask_question_float(char *question)
{
  return ask_question(question, is_float, make_float).f;
}
```

För att göra `ask_question_string()` måste vi tyvärr gå händelserna
i förväg en aning och använda en funktion, `strdup()` vars funktion
är svårt att förklara med den begränsade del av C som vi har tittat
på hittills. Den inlästa strängen i din `ask_question()` är ju redan
en sträng, så man kan tycka att man kunde returnera den rakt av, men
så är inte fallet!

Skriv så här längst upp i filen så länge. Senare kommer vi att
skriva en egen version av denna kod:
```c
extern char *strdup(const char *);
```

Det är nämligen så att din inläsningsbuffert (iallafall om du har
använt en array, som är det enda vi gått igenom hittills) är knuten
till den omslutande funktionen -- och efter att funktionen är klar
kan minnet där texten lästes in komma att återanvändas när som helst.
Vi måste därför skapa en _kopia_ av strängen som är fri att skickas
vart som helst. Detta görs med hjälp av funktionen `strdup()` som
finns i `string.h` och som duplicerar en sträng. Exemplet nedan
skapar en kopia och skriver ut både kopian och originalet:

```c
char *original = "foo bar baz!"
char *kopia = strdup(original);
printf("%s\n%s\n", original, kopia);
```

Nu kan vi skriva klar `ask_question_string()` så här:

```c
char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).s;
}
```


## Uppdatera `utils.h` och `utils.c`

Nu är det dags att uppdatera det generella biblioteket `utils`.
Kopiera in dina funktioner och typalias dit. Där bör nu ligga
följande funktioner (åtminstone), i någon ordning:

* Typen `answer_t`
* Typen `check_func`
* Typen `convert_func`
* Deklarationen `extern char *strdup(const char *);`
* `int read_string(char *buf, int buf_siz)`
* `bool is_number(char *str)`
* `bool is_float(char *str)` och `answer_t make_float(char *)` (inte obligatoriska)
* `bool not_empty(char *str)`
* `answer_t ask_question(char *question, check_func check, convert_func convert)`
* `char *ask_question_string(char *question)`
* `int ask_question_int(char *question)`
* `double ask_question_float(char *question)` (inte obligatorisk)

Själva definitionen av funktionerna (med koden i) skall ligga i
`utils.c`. Funktionsprototyperna (t.ex. `bool is_number(char
*str);`), `extern...` samt typedef:arna skall ligga i `utils.h`.

Senare under kursen skall vi diskutera mer ingående hur man skapar
bibliotek/moduler, placering av funktioner och definitioner,
inkapsling och synlighet.


## *Grand Finale! Kompilera om Gissa Talet mot nya `utils` (Skall redovisas)

Om du har gjort allt rätt kan du kompilera om ditt Gissa
Talet-program från föregående labb mot ditt nya `utils`-bibliotek:

    > gcc -Wall utils.c guess.c

Du borde inte få några varningar vid kompilering (såvida du inte
fick det förut -- vilket du inte borde ha gjort!) och om du kör
programmet igen skall det fungera precis som förut.

Verifiera att så är fallet och fixa till eventuella buggar!


# Frivilliga extrauppgifter

## Trim

En funktion som är vanlig i moderna strängbibliotek är funktionen
`trim()` (aka `strip()`) som tar bort "skräptecken" i början och
slutet av en sträng. Exakt vad ett skräptecken är naturligtvis
subjektivt, men låt oss definiera det som "whitespace" -- enligt
definitionen av `isspace()` i `ctype.h`. (Använd gärna `man
isspace` för att ta reda på mer.)

Du skall skriva funktionen `trim()` som tar in en sträng och
helt enkelt tvättar bort allt "skräp".

    trim("  hej  ")   => "hej"
    trim("  h ej  ")  => "h ej"
    trim(" hej  \n")  => "hej"

Funktionens signatur:

```c
char *trim(char *str);
```

Förslag till implementation:

1. Ta reda på det första tecknet från vänster, _S_, som inte är skräp (`!isspace()`)
2. Ta reda på det första tecknet från höger, _E_, som inte är skräp (`!isspace()`)
3. Kopiera varje tecken från _S_ till och med _E_ till början av `str`
4. Skriv in ett `'\0'`-tecken efter det sista flyttade tecknet
5. Returnera `str`

Lägg till `trim()` i `utils`-biblioteket!

Du kan testa att ditt program är korrekt med hjälp av följande
testprogram:

```c
#include "utils.h"

int main(void)
{
  char str1[] = "  hej  ";
  char str2[] = "  h ej  ";
  char str3[] = "  hej\t ";
  char str4[] = "  hej\t \n";

  char *tests[] = { str1, str2, str3, str4 };

  for (int i = 0; i < 4; ++i)
    {
      print("Utan trim: '");
      print(tests[i]);
      print("'\nMed trim:  '");
      print(trim(tests[i]));
      println("'\n");
    }
  return 0;
}
```

Sä här skall en körning av programmet se ut:

    Utan trim: '  hej  '
    Med trim:  'hej'

    Utan trim: '  h ej  '
    Med trim:  'h ej'

    Utan trim: '  hej	 '
    Med trim:  'hej'

    Utan trim: '  hej
    '
    Med trim:  'hej'

(En modifierad version av detta program var nyligen på ett kodprov.)

Alternativ implementation:

1. Gå genom strängen från vänster till höger, och så länge enbart
   skräptecken hittats, gör ingeting
2. Från det att första skräptecknet hittats, kopiera varje tecken
   som passerats till början av strängen (första gången till
   position 0, andra till position 1, osv.) -- kopiera även
   skräptecken. Första gången ett skräptecken kopieras efter att
   ett eller flera icke-skräptecken har kopierats, kom ihåg platen
   _P_ för det skräptecknet (vi är bara intresserade av det sista
   -- högraste -- _P_:t)
3. När du når slutet på strängen, skriv `\0` i _P_
