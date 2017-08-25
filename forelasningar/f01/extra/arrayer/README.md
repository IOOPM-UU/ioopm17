Arrayer
=======

En array i C kan ses som en ordnad samling värden av en viss typ.
De påminner om listor (som i Haskell) men är olika i flera
avseenden. Till skillnad från listor så ligger arrayer i ett enda
sammanhängade stycke i minnet, vilket gör att man kan indexera
(läsa och skriva element) på konstant tid. Det innebär också att
arrayer i allmänhet inte har dynamisk storlek. När man skapar en
array så anger man dess storlek, och den storleken ändras aldrig.
**Man kan alltså inte "lägga till" och "ta bort" element på samma
sätt som med en lista**.

Nu ska vi skriva ett program som använder arrayer:

1. Öppna en ny fil i Emacs (`C-x C-f`) och döp den till `array.c`

2. Skriv in följande programskelett:

  ``` c
    int main(){
      int a[5];
      return 0;
    }
  ```

3. Raden `int a[5];` deklarerar en array som heter `a` som har
  plats för fem heltalselement. Klamrarna efter namnet visar att
  `a` ska vara en array av `int`ar och inte bara en `int`. Femman
  mellan klamrarna anger hur många element arrayen ska ha plats
  för.

4. Klammernotationen används också för att *indexera* ("välja
  element")i arrayer. Följande rader skriver in några värden i
  arrayen. Skriv in dem mellan deklarationen av `a` och
  `return`-satsen. Notera att arrayer indexeras från 0.

  ``` c
    a[0] = 42;
    a[1] = 10;
    a[2] = 10 - (5 + 6);
    a[3] = a[0] + a[1];
    a[4] = 999;
  ```

5. När man arbetar med arrayer använder man ofta loopar för iterera
  över samtliga element. Här är en loop som skriver ut alla element i
  `a`. Skriv in den innan `return`-satsen. Du behöver inte förstå
  hur `printf` funkar än.

  ``` c
    for (int i = 0; i < 5; ++i){
      printf("a[%d] = %d\n", i, a[i]);
    }
  ```

För att `printf` ska gå att använda så måste man skriva in
`#include <stdio.h>` högst upp i filen. Raden berättar för
kompilatorn att den ska börja med att läsa in filen `stdio.h`,
som innehåller information om funktioner som används för in- och
utmatning.

Loopen följer ett mycket vanligt mönster. Loopvariabeln `i` antar
alla värden mellan 0 och arrayens högsta index (som i det här
fallet är 4), och i varje iteration av loopen görs något med
värdet `a[i]`.

6. Kompilera och kör programmet. Verkar rätt värden skrivas ut?

7. Du ska nu skriva en loop som följer samma mönster. Istället för
  att skriva om allting kan du kopiera loopen (`M-w` kopierar,
  `C-y` klistrar in. Markera text genom att hålla ned `<shift>`
  samtidigt som du flyttar markören, alternativt tryck `C-<space>`
  för att starta markering och flytta runt markören). Lägg den nya
  loopen innan den första och byt ut `printf`-anropet mot raden
  `a[i] = i`. Vilka värden ligger nu i arrayen? Kompilera och
  prova!

8. Hur kan man ändra på loopen ni skrev i det förra steget så att
  arrayen istället innehåller kvadraten av motsvarande index (alltså
  `{0, 1, 4, 9, 16}`)?


## Mer arrayer

1. Öppna filen `rooms.c`.

2. Det här är ett mycket enkelt program som skriver ut en lista
  av universitetsanställda och i vilket rum på Polacksbacken de
  sitter. Namnen lagras i arrayen `names` och rumsnumren i
  arrayen `rooms`. Här är arrayerna initierade med värden direkt
  istället för att de skrivits in ett och ett. Notera också att
  ingen längd har angivits mellan klamrarna. Eftersom vi berättar
  vilka element som ska finnas i arrayen från början så kan
  kompilatorn räkna ut det själv.

  Loopen är i princip likadan som den i `array.c`, förutom att vi
  har flyttat ut längden till en variabel `length`. Vad borde
  programmet skriva ut? Kompilera och kör!

3. Prova nu att lägga till Stephan Brandauer i "databasen" (han
  sitter också i rum 1357). Vilka variabler behöver man ändra på för att
  loopen ska skriva ut hela databasen?

4. Vad händer om man sätter variabeln `length` till något större tal
  än antalet element i arrayerna? Kompilera och kör!

  Förmodligen hände en av två saker:
  * Programmet kraschade och skrev ut meddelandet `Segmentation
      fault`. Detta är felet som uppstår när ett program försöker
      läsa eller skriva minne som den inte har tillgång till. I
      det här fallet försökte programmet läsa ett värde utanför
      arrayens gränser. Prova att köra programmet i gdb (utan
      breakpoints) för att se vilken rad programmet kraschar på!
  * Programmet körde men skrev ut obegripliga namn och rumsnummer
    efter den vanliga utskriften. I det här fallet hade programmet
    tillgång till minnet utanför arrayerna, men eftersom
    programmet inte skrev något till de minnesadresserna så kan
    det ligga vilket skräp som helst där.

5. Vad händer om man anger en felaktig längd mellan klamrarna på
  någon av arrayerna? Vad säger kompilatorn? Prova att ange både
  ett för högt och ett för lågt tal.


## Tillämpning med memoisering

I denna uppgift skall vi använda arrayerna för att förbättra
[fibonacciprogrammen från rekursionshandledningen](../rekursion).
Det krävs relativt få ändringar, men de kan vara lite kluriga att
tänka ut.

Inom matematiken (och den rena funktionella programmeringen) är en
funktion *f* "stabil" i det avseendet att om *f(x)=y* vid någon
tid *t* så gäller att *f(x)* alltid ger *y*. I de flesta
programspråk behöver detta dock inte vara fallet -- om *f* betyder
"ge mig första elementet" och *x* är en lista *vars innehåll kan
förändras* är det enkelt att se att två förekomster av *f(x)* inte
behöver ge samma resultat om *x* kan ha ändrats. Inom matematiken
och i ren funktionell programmering kan *x* inte förändras (eller
om *x* förändras så anser vi det vara en annan lista som inte
längre är *x*, analogt med Herakleitos klassiska uttalande om
floder).

Om vi för ett ögonblick glömmer *sidoeffekter* är det enkelt att
inse att en funktion som är stabil i bemärkelsen ovan (ofta kallar
man detta för en "ren funktion") aldrig behöver beräknas mer än en
gång. En av anledningarna till att den rekursiva
Fibonacci-implementationen ovan är så mycket långsammare än den
iterativa är att den kommer att beräkna samma fibonaccital flera
gånger (varför!?).

I denna uppgift skall vi återbesöka den rekursiva
Fibonacci-implementationen. Först skall vi ta reda på hur mycket
långsammare den är en den iterativa implementationen, sedan hur
många gånger varje fibonaccital räknas ut vid en given fråga, och
sist använda oss av en enkel optimiseringsteknik för att förbättra
dess prestanda avsevärt.


### Prestandamätning med time

Gå tillbaka till [fibonacci-programmen](../rekursion) och kompilera både
den rekursiva och den iterativa implementation. Följ
instruktionerna nedan och justera för eventuella ändringar i
katalognamn som du gjort efter eget huvud.

```
  foo> cd till rätt katalog!
  foo> make fib
```

Nu skall programmen vara kompilerade och heta `fib-rec` respektive
`fib-iter` (programmet `make` används för att köra så kallade
byggskript. I filen `Makefile` står byggskriptet som kördes med
kommandot ovan. Du kommer få lära dig använda `make` senare i
kursen). Det lilla programmet `time` låter oss på ett enkelt sätt
jämföra körtiden hos program. Du kan läsa mer om hur du skall
tolka utdatat med hjälp av `man time`. Nedan ser du hur du kan
mäta körtiden för det rekursiva programmet för `fib(5)`.

```
  foo> time ./fib-rec 5
  ... resultatet skrivs ut
```

Generellt räcker det inte med att bara göra en mätning för att
avgöra om eller hur mycket ett program är långsammare än ett
annat. I de flesta fall är körtiden en funktion av indatats
storlek, och man kan vaska fram ett förhållande genom att göra
flera mätningar och t.ex. rita en graf. Gör därför 10 mätningar
för `fib(n)` där `n` går från 1 till 50 och visualisera resultatet
i ett diagram där y-axeln är körtid i millisekunder och x-axeln
avser storleken på $n$. Vad visar den? Går det att få fram svar
för samtliga uträkningar?


### Hur många gånger räknas varje tal ut?

Vi skall nu modifiera `fib-rec` för att hålla reda på hur
många "onödiga" uträkningar som görs för en viss fråga. Ett
enkelt sätt är att skapa en "tabell" där den `i`:te kolumnen
håller reda på hur många gånger `fib(i)` har räknats ut. Detta kan
enkelt åstadkommas med hjälp av en array av heltal. En sådan kan
deklareras på detta vis (ovanför fib-funktionen):

``` c
  int calculations[128];
```

Deklarationen `int calculations[128]` skapar en global variabel
`calculations` som håller en array av 128 heltal vars värden är
noll (observera att det anses som dålig programmering att använda
globala variabler -- framledes skall vi se hur vi kan undvika
detta). Notera att samma deklaration inuti en funktion hade gett
upphov till en array med mer eller mindre slumpartade värden
(Dessa värden uppstår av att det kan ligga bitar i minnet på den
plats där arrayen skapas som då tolkas som siffror. Mer om detta
senare). Då hade vi varit tvungna att manuellt sätta alla värden
till noll, till exempel med en loop.

Nu vill vi för varje anrop till `fib(i)`, på den `i`:te positionen
i `calculations`, öka det värde som finns där (initialt 0) med
1. Detta skulle kunna se ut så här (där `i` bör ersättas med något
lämpligare):

``` c
  calculations[i] += 1;
```

Stoppa in denna rad (eller gör efter eget huvud) på ett lämpligt
ställe i programmet.

Slutligen vill vi, sist i `main`-funktionen, men före
`return`-satsen, skriva ut resultatet. Det kan göras så här:

``` c
  for (int i=0; i<128; ++i) {
    printf("fib(%d) was calculated %d times\n", i, calculations[i]);
  }
```

När programmet körs för `fib(6)` bör denna utdata inkludera följande:

```
  fib(0) was calculated 5 times
  fib(1) was calculated 8 times
  fib(2) was calculated 5 times
  fib(3) was calculated 3 times
  fib(4) was calculated 2 times
  fib(5) was calculated 1 times
  fib(6) was calculated 1 times
  fib(7) was calculated 0 times
  ...
  fib(127) was calculated 0 times
```

Fundera över vad som behöver ändras i föregående kodlistning för
att bara `fib(0)` till fib(6) skall skrivas ut så att man slipper
(i detta fall fler än 100) onödiga utskrifter för tal som man inte
försökt räkna ut. Lösningen skall vara generell och fungera för
`fib(i)` där `i` är mindre än längden på `calculations`. (Fundera
över varför det är så!)


### Memoisering

Nu vill vi optimera programmet så att första gången som `fib(i)`
räknas ut sparas resultatet -- alla andra gånger använder man det
sparade resultatet av uträkningen. Denna teknik kallas memoisering
och används i rena funktionella programspråk (d.v.s. inte i C).

Spara ditt modifierade program från föregående uppgift under ett
nytt filnamn med `C-x C-w` och ersätt uträkningsräknaren för
`fib(i)` på plats `i` med värdet av `fib(i)`. Byt även namn på
`calculations` till `memoised_fib_values` som är ett bättre namn
på variabeln, och ta bort sammanställningen av antalet anrop på
slutet. Försök att göra detta effektivt i Emacs, t.ex. med `M-x
query-replace` som söker och ersätter, och `C-k` som tar bort en
hel rad från markören.

Det skulle kunna se ut så här (modifiering av rad 11 i `fib-rec.c`):

``` c
  int fib_n = fib(n-1) + fib(n-2);
  memoised_fib_values[n] = fib_n;
  return fib_n;
```

Notera att C tillåter att vi skriver ovanstående utan den
temporära variabeln:

``` c
  return memoised_fib_values[n] = fib(n-1) + fib(n-2);
```

Detta anses dock svårläsligt och därmed felbenäget.

När varje uträknat fibonaccital sparats i arrayen kvarstår att
också använda dessa memoiserade (sparade) resultat. För basfallen
0 och 1 behöver vi inte bry oss om memoiserade resultat eftersom
svaren då är givna, men för `n` > 1 bör vi först titta i
`memoised_fib_values[n]` för att se om svaret redan är uträknat.
Så är fallet om det värde som finns sparat där är större än 0
(varför?!), och då kan detta värde direkt returneras. Annars skall
värdet räknas ut och sparas.

Skriv klart detta program själv och jämför med "facit",
`fib-memo.c` som finns i samma katalog som `fib-iter.c` etc. När
du är klar, använd `time` och undersök prestandaförbättringen
jämfört med `fib-rec`.

### Tänkvärt
* C bygger på några få enkla koncept -- dessa går fort att
  lära sig, men att lära sig hur de kan kombineras till felfria
  program är inte en parkpromenad! Läs andras kod och skriv egen
  kod så mycket du kan!
* Om du är van vid Haskell, Ruby, Python, Java etc. så tycker du
  kanske att C bjuder på få funktioner -- vad C ger i gengäld är
  hög prestanda och låg overhead och enorm kontroll över exakt vad
  som pågår i ett program.
