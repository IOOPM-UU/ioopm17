# Labb 1: Grundläggande koncept

**OBS!!!**

På lab 5 kommer du att bli ombedd om att spara alla dina labbar
på GitHub! Se därför till att inte kasta bort eller slarva bort
någon fil innan dess!

**OBS!!!**


## Steg 1: Emacs-fix

Som du säkert vet kommer vi att använda Emacs som editor på
kursen. (Notera att med Emacs avses också vi/vim.) Emacs är en
utökningsbar editor som är skriven i C och programspråket
Emacs-lisp. Man utökar och raffinerar sin egen Emacs genom
ytterligare paket skrivna i Emacs-lisp. Man kan skriva dessa paket
själv, eller ladda ned dem och installera dem själv eller via
Emacs inbyggda pakethanterare.

**Tips** I kursrepots [extramaterial](../extramaterial) finns
screencasts och en lathund om grundläggande Emacs-användning.

Nu följer två olika uppsättningar instruktioner beroende på om du
kör Linux eller OS X/macOS. För dig som kör Windows har vi tyvärr
ingen handledning, men vi råder dig att installera Linux under
kursens gång då det är en bättre programmeringsmiljö för den
C-programmering som vi skall göra.

### Linux

Kör `emacs --version` i terminalen. Om du har en yngre Emacs än
version 24 skall måste du uppgradera den för att nedanstående
skall fungera.

    > cd ~
    > mkdir .emacs.d
    > cd .emacs.d
    > curl http://wrigstad.com/ioopm/emacs-setup-linux.zip -o e.zip
    > unzip e.zip
    > rm -f e.zip

Notera att om du skriver fel i den långa URL:en ovan kommer du
fortfarande att få en fil `e.zip` men som inte går att
packa upp. Om `unzip`-steget inte fungerar -- kontrollera din
stavning i `curl`-steget!

### OS X/macOS

Kör `emacs --version` i terminalen. Om du har en Emacs som är yngre än
version 24 skall måste du uppgradera den för att nedanstående
skall fungera. Vid behov kan du ladda hem och installera en
okonfigurerad version från
[https://emacsformacosx.com/](https://emacsformacosx.com/) som är
tillräckligt ny. Om du vill att din nya version ska öppnas när du
skriver `emacs` i terminalen kan du skapa ett alias. Skriv
följande i en terminal:

    > cd ~                  # Gå till hemkatalogen
    > emacs .bash_profile   # Öppna din profil

I den öppnade filen, lägg till följande rad:

    alias emacs=/Applications/Emacs.app/Contents/MacOS/Emacs

Spara och avsluta (`C-x C-s` `C-x C-c`) och kör ytterligare ett
kommando i terminalen:

    > source ~/.bash_profile

Nu kommer du att öppna Emacs i ett eget fönster när du skriver
`emacs`. Om du vill köra Emacs i terminalen kan du använda
kommandot `emacs -nw`.

För att skaffa kursens Emacs-konfiguration, kör nedanstående i en
terminal.

    > cd ~
    > mkdir .emacs.d
    > cd .emacs.d
    > curl http://wrigstad.com/ioopm/emacs-setup-osx.zip -o e.zip
    > unzip e.zip
    > rm -f e.zip

Notera att om du skriver fel i den långa URL:en ovan kommer du
fortfarande att få en fil `e.zip` men som förstås inte går att
packa upp. Om `unzip`-steget inte fungerar -- kontrollera din
stavning i `curl`-steget!

## Steg 2: Setup

Nu är det dags att skapa en katalog för kursen i din hemkatalog på
Linux-maskinerna (eller på din egen dator, eller båda). Ett
lämpligt namn för denna katalog är `ioopm`. Sedan skall vi skapa en
underkatalog `lab1`, en tom fil `hello.c` i den och starta Emacs
för att editera filen.

    > cd ~              # gå till din hemkatalog
    > mkdir ioopm       # skapa underkatalogen ioopm
    > cd ioopm          # gå in i ioopm-katalogen
    > mkdir lab1        # skapa underkatalogen lab1
    > cd lab1           # gå in i lab1-katalogen
    > touch hello.c     # skapa en tom fil hello.c
    > emacs hello.c &   # starta Emacs för att editera filen
    >

Om du kör på institutionens Linux och inte har gjort någon egen
konfigurering kan du växla mellan program med `Alt+Tab`. Vi kommer
att använda **editorn** för att skriva text och **terminalen** för
att kompilera och köra programmet. Pröva att växla några gånger
mellan programmen.

Du bör kunna använda `Ctrl+Win+vänsterpil` för att maximera det
aktuella fönstret på skärmens vänstra halva och motsvarande för
den högra. Det är ett bra sätt att ha både terminalen och editorn
så att man kan se all information alltid.

**Nu är du redo att börja med labben!**

Var noga med att spara en version av varje färdigt program! Ta för
vana att experimentera i en ny fil som du antingen skapar tom eller
kopierar från en som fungerar.

## Hello, world!

Det klassiska första programmet att skriva i varje programspråk är "Hello, world!"

Det finns många sätt att skriva detta program. Ett enkelt sätt är:

```c
#include <stdio.h>

int main(void)
{
  puts("Hello, world!");
  return 0;
}
```

Skriv av (eller kopiera, men ännu hellre skriv av) programmet ovan
i en editor och döp det till `hello.c`. Alla C-program startar i
funktionen `main()` (aka "`main()`-funktionen") som är en funktion
som returnerar ett heltal som berättar för det underliggande
operativsystemet om körningen av programmet gick bra. Tillsvidare
returnerar vi alltid 0.

Kompilera programmet med `gcc hello.c` -- nu skapas filen `a.out`
som du kör så här: `./a.out`. Så här kan det se ut i terminalen:

    > emacs hello.c &       # startar Emacs
    > gcc hello.c           # kompilerar hello.c
    > ls                    # listar filerna i terminalen
    a.out   hello.c
    > ./a.out               # kör a.out
    Hello, world!           # programmets output
    > _                     # väntande kommandoprompt

Funktionen `puts()` skriver ut en sträng på terminalen (`puts` = "put
string"). Låt oss nu experimentera med att använda funktionen
`printf()`. Denna funktion tar ett variabelt antal argument. Börja
med att ändra `puts("Hello, world!");` till `printf("Hello,
world!");`, kompilera om och kör programmet igen. Kan du se någon
skillnad?

Skillnaden är add `printf()` inte automatiskt skriver ut en
radbrytning efter utskriften. Sätt dit det genom att skriva
`\n` efter `!`, dvs. `printf("Hello, world!\n");`.

Funktionerna `puts()` och `printf()` är två helt olika funktioner.
Den första skriver ut en enskild sträng medan den andra kan
användas för att skriva ut en mängd olika saker: strängar, heltal,
flyttal, minnesadresser etc.

**Pröva gärna** att titta på skillnaden mellan `puts()` och
`printf()` genom att skriva `man puts` och `man printf` i
terminalen och titta på manualsidorna för funktionerna. Du
scrollar med mellanslag och avslutar med **q**. (Du kan skriva
`man pager` för att läsa vilka kortkommandon som finns för att
läsa manualsidor med man-kommandot. Du kan också skriva `man man`
för att få veta mer om man-kommandot.)

Pröva att ändra utskriften så här:

```c
char *msg = "Hello, world!";
int year = 2017;
printf("%s in the year %d\n", msg, year);
```

Vi deklarerar nu en _variabel_ `msg` som är en sträng (i C är
typen för sträng `char *`, mer om detta senare) vars innehåll är
texten "Hello, world!" och en variabel `year` som innehåller
heltalet 2017. (Minns att en typ är ett namn på en samling värden
som delar vissa egenskaper. I C har vi t.ex. en typ för heltal, en
för flyttal, etc.)

Sedan säger vi åt `printf()` att skriva ut en sträng (`%s`) följt
av texten " in the year ", följt av ett heltal (`%d`) följt av en
radbrytning (`\n`). Sedan skickar vi med `msg` och `year` -- i samma 
ordning som `%s` och `%d` (vad händer om du råkar byta plats på dem?).

Observera att `printf()` nu tar 3 argument. Funktionen tar alltid
in en _formatsträng_ (i vårt exempel `"%s in the year %d\n"`) och
sedan ytterligare ett argument för varje "styrkod" (`%s` och `%d`
i detta exempel) som finns med i formatsträngen.

Från Haskell är du van vid att man binder namn till värden, t.ex.
`let x = 5 in BLAHRG`. Där är `x` en konstant vars värde är `5`.
När vi har denna typ av namnbindningar kan vi söka och ersätta
alla förekomster av `x` med `5` i `BLAHRG` och få samma resultat.

Variabler i C fungerar annorlunda i och med att deras värden kan
ändras! `int x = 5; ...` betyder att vi har skapat ett namn, `x`,
som avser ett heltal, som initialt är `5`, men som kan komma att
ändra värde. Om `...` ovan t.ex. är

    printf("%d\n", x);
    x = 42;
    printf("%d\n", x);

kommer första utskriften av `x` att bli 5 och den andra 42.

### Mini-övning

Skriv av följande program och ändra `...` till kod som byter plats
på värdena i variablerna `x` och `y`:

```c
#include <stdio.h>

int main(void)
{
  int x = 1;
  int y = 2;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  puts("=====");
  ...
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  return 0;
}
```

**Tips** Använd en tredje variabel `tmp` för att "komma ihåg"
värdet på `x` så att du kan skriva över `x` med `y` och sen `y`
med `tmp`. Var noggrann med skillnaden mellan `int x = 1`, som
introducerar en _ny_ variabel `x` med värdet 1, och `x = 1`, som
ändrar värdet på en _existerande_ variabel `x` till värdet 1.

Om du gjort rätt borde programmet ge följande output när du
kompilerar och kör det:

    > gcc swap.c
    > ./a.out
    x = 1
    y = 2
    =====
    x = 2
    y = 1

## Skriv ut talföljden 1--10

Skriv ett program `p1` som, när det körs, skriver ut talen 1 till 10 så här:

    > gcc p1.c
    > ./a.out
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10

Du ska använd en **for-loop** och kan utgå från följande
programskelett:

```c
#include <stdio.h>

int main(void)
{
  int i = 1;              // deklaration och initiering av iterationsvariabeln
  while (i <= 10)         // iterationsvillkor (utför blocket så länge i är mindre än 11)
  {                       // loop-kropp (utförs så länge iterationsvillkoret är uppfyllt)
    printf("%d\n", 1);      // skriv ut 1, och en radbrytning
    i = i + 1;              // öka i:s värde med 1 (förändring av iterationsvariabeln)
  }
  return 0;
}
```

Detta program är trasigt: det skriver ut 1 hela tiden. Börja med att
fixa det (ledning: titta anropet till `printf()`), och skriv sedan om
`while`-loopen med en for-loop som har följande syntax:

```c
for ( deklaration och initiering av iterationsvariabel ;
      iterationsvillkor ;
      förändring av iterationsvariabel )
  {
    loop-kropp
  }
```

Det så-kallade _preprocessormakrot_ `#include <stdio.h>` talar om
för C-kompilatorn att vi vill använda standardbiblioteket för
input/output, som alltså heter `stdio`. Filen `stdio.h` som finns
någonstans i filsystemet innehåller deklaration av funktioner och
datatyper som blir tillgängliga i och med att man skriver
`#include <stdio.h>` i den fil som vill använda biblioteket.


## Skriv ut talföljden 10--1

Kopiera programmet `p1.c` ovan till `p2.c` och skriv om det så att
talföljden går ned från 10 till 1 istället:

    > gcc p2.c
    > ./a.out
    10
    9
    8
    7
    6
    5
    4
    3
    2
    1

## Nästade loopar

Nu skall vi experimentera med nästade loopar, dvs. loopar vars
loopkroppar innehåller loopar. Kopiera `p1.c` till `p3.c` och
skriv om programmet så att det istället för tal skriver ut en
ökande mängd `#`. Sist skall det skrivas ut hur många `#`
(brädgårdar) som skrev ut:

    > gcc p3.c
    > ./a.out
    #
    ##
    ###
    ####
    #####
    ######
    #######
    ########
    #########
    ##########
    Totalt: 55
    > _

Skriva ut _N_ stycken `#` kan enkelt göras med en loop som i _N_
varv skriver ut ett `#` i varje varv utan efterföljande
radbrytning.

**Tips** Ett program ska ofta göra mer än en sak. Börja aldrig med
att försöka skriva hela programmet på en gång. Om du inte kan
skriva en enskild loop som skriver ut _N_ stycken `#` så kommer du
inte kunna skriva ett program som skriver ut _1_ till _N_ stycken
`#`. Försök alltid hitta delproblemen och lös dem var och en för
sig. Här är ett förslag på delproblemen för den här uppgiften som
alla kan lösas en i taget:

1. Skriv en loop som itererar från 1 till 10 (redan löst i `p1.c`).
2. Skriv en loop som skriver ut _N_ stycken brädgårdar (för något
   värde på _N_).
3. Ändra loopen i 1. så att brädgårdar skrivs ut istället för
   tal (använd loopen från 2.).
4. Skriv ut summan av alla utskrivna brädgårdar.

## Kommandoradsargument 1/2

Kopiera `p3.c` till `p4.c` -- nu skall vi utöka programmet så att
det går att skicka in antalet staplar som skall skrivas ut, samt
hur snabbt staplarna skall växa. Här är tre exempelkörningar av
programmet:

    > gcc p4.c
    > ./a.out 3 2
    ##
    ####
    ######
    Totalt: 12
    > ./a.out 0 25
    Totalt: 0
    > ./a.out 4 4
    ####
    ########
    ############
    ################
    Totalt: 40
    > ./a.out
    Usage: ./a.out rows growth
    > _

Kommandoradsargument skickas automagiskt in som argument till
`main()`-funktionen. Vi kan skriva programmet `eko` så här (som
bara "ekar" alla kommandoradsargument):

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; ++i)
  {
    puts(argv[i]);
  }
  return 0;
}
```

Observera nu att `main()`-funktionens _signatur_ ser annorlunda ut. Två
nya _parametrar_ har lagts till:

1. `int argc` -- heltalet `argc` som håller reda på hur många argument som skickades in
2. `char *argv[]` -- en _array_ av strängar som motsvarar kommandoradsargumenten

Minns att `char *` är C:s strängtyp -- det efterföljande `[]` visar
att `argv` inte är bara en sträng, utan en hel array av strängar.

Minns att **en array** är som en lista -- dvs. en sekvens av
värden, men till skillnad från en lista (i t.ex. Haskell) kan en
array inte utökas. Om arrayen `arr` är en array med tre element
kan vi komma åt element 1 med `arr[0]`, element 2 med `arr[1]` och
element 3 med `arr[2]`. Om vi skriver `arr[3]` för att komma åt
det 4:e elementet är resultatet skräp, och exakt vad det betyder
kan variera mellan olika implementationer av kompilatorer, etc.
Det är alltså något som vi skall undvika, men som kompilatorn inte
skyddar oss emot.

Arrayer indexeras från 0, dvs. `puts(argv[0])` skriver ut den första
strängen i `argv`. `argv[0] = "Ivor Cutler"` gör så att den första
strängen i `argv`-arrayen blir strängen "Ivor Cutler".

När programmet ovan körs skriver det ut sina kommandoradsargument så här:

    > gcc eko.c
    > ./a.out hej hopp fallera 42
    ./a.out
    hej
    hopp
    fallera
    42
    > _

I ovanstående körning anropas `main()`-funktionen med `argc` = `4`
och `argv` = `["./a.out", "hej", "hopp", "fallera", "42"]`.

Observera att den första strängen i `argv` alltid är det namn som
man använde för att starta programmet -- alltså `./a.out` i alla
våra exempel hittills.

Observera att `"42"` är en sträng och att `42` är ett heltal -- de
är alltså olika datatyper som inte är kompatibla. Man
kan konvertera strängen `"42"` till talet `42` med hjälp av
funktionen `atoi()`:

```c
char *str = "42";
int num = atoi(42);
printf("%s == %d?\n", str, num);
```

`atoi()` står för _ASCII to Integer_. (En av anledningarna till
att namnen på många funktioner är så korta och usla är att man i
förhistorisk tid kunde tjäna många sekunder på att slippa skicka
"onödiga" tecken över väldigt långsamma linor när man skulle
programmera via terminaler. Det är inte en giltig anledning
längre, men det är svårt att ändra 30+ år gamla
standardbibliotek.)

För att använda `atoi()` måste programmet _inkludera_
standardbiblioteket `stdlib.h`:

```c
#include <stdio.h>   // stod redan
#include <stdlib.h>
```

(Senare skall vi skriva en funktion som konverterar från ett
heltal till en sträng.)

I körningsexemplet ovan detekterar programmet om det körs utan
några argument (eller -- mer korrekt -- utan andra argument än
programmets namn) och skriver i så fall ut en hjälptext:

    Usage: ./a.out rows growth

Vi kan använda en `if`-sats för att kontrollera om antalet
argument är felaktigt.

```c
if (antalet argument < 2 || antalet argument > 3)
{
  skriv ut felmeddelande
}
else
{
  utför uppgiften
}
```

Den märkliga `||`-symbolen är ett logisk _eller_ dvs. `a || b` är
sant om `a` är sant, eller om `b` är sant (eller om båda är
sanna).

**Nu kan du skriva klart programmet!** Betänk följande:

* Arrayer indexeras från 0
* `argv[0]` är programmets namn
* Programmet blir lättare att läsa och förstå om du sparar
  `argv[1]` och `argv[2]` i variabler med vettiga namn.
* Programmet klarar inte av kommandoradsargument som inte är tal


## Primtalstest

Med hjälp av vad vi lärt oss hittills kan vi nu skriva ett enkelt
program som tar emot ett tal som kommandoradsargument och avgör om
det är ett primtal. Utgå från `p4.c` och kopiera det till `p5.c`.

En enkel algoritm för att kontrollera om talet _N_ är ett primtal
är att pröva om _x_ * _y_ = _N_ för alla kombinationer av _x_ och
_y_ i intervallet 2 till _N_. Om det inte går att hitta ett sådant
_x_ anser vi att _N_ är ett primtal. Två tal kan jämföras med
operatorn `==`, t.ex. så här:

```c
if (a == b)
{
  puts("Lika");
}
else
{
  puts("Inte lika");
}
```

**OBS!** Ett vanligt nybörjarfel är att man blandar ihop `a == b`,
som kontrollerar om `a` och `b` har samma värde, med `a = b` som
skriver värdet av `b` till variabeln `a`. Det är ett svårt fel att
upptäcka i början, så var försiktig!

Med en nästad loop kan du prova alla kombinationer av _x_ och _y_
genom att räkna ut `2*2`, `2*3`, ..., `2*(N-1)`, `3*2`, `3*3`...
och se om någon produkt är lika med _N_.

En _optimering_ av algoritmen ovan är att inte växa _x_ högre än
roten av _N_. Roten av _N_ kan räknas fram med
biblioteksfunktionen `sqrt()`. Optimeringar kan vi göra först när
vi fått en första version av programmet att fungera. 

**OBS!** Om du har problem med att kompilera program med `sqrt()`
i för att en sådan funktion inte finns, lägg till `-lm` till
kompileringen. Det betyder "länka mot matematikbiblioteket", 
dvs. sök också i matematikbiblioteket efter funktioner som 
programmet kan vilja använda. 

```c
float roten_ur_n = sqrt(N);
```

För att använda `sqrt()` måste programmet _inkludera_
matematikbiblioteket `math.h` på samma sätt som du inkluderat
`stdio.h` och `stdlib.h` tidigare: `#include <math.h>`.

Notera att `sqrt()` returnerar ett _flyttal_. Hjälpfunktionen
`floor()` skapar ett heltal från ett flyttal och avrundar nedåt.
Gränsen för _x_ blir därför:

```c
float tmp = sqrt(N);
int limit = floor(tmp) + 1;
```

Det går också att skriva detta program utan variabeln`tmp`. (Gör gärna det -- här ville vi lyfta fram de två delstegen.)

Skriv klart programmet och testa det:

    > gcc p5.c
    > ./a.out 7
    7 is a prime number
    > ./a.out 2
    2 is a prime number
    > ./a.out 4
    4 is not a prime number

Anser programmet att 1 är ett primtal?
Anser programmet att 0 är ett primtal?


## Största gemensamma delare (GCD)

Skriv nu ett program som tar emot två positiva tal och skriver ut deras
största gemensamma delare med hjälp av Euklides algoritm:

    gcd(a, b) = a                om a = b
    gcd(a, b) = gdc(a - b, b)    om a > b
    gcd(a, b) = gdc(a, b - a)    om a < b

Använd en **while-loop** eller en **for-loop** för att lösa
problemet. Varje varv i loopen kommer variabeln `a` eller
variabeln `b` att ändra värde beroende på vilken som innehåller det
största värdet. Till slut är de lika och då har vi svaret.

Du kan utgå från `p5.c` och skapa `p6.c` eller skriva programmet
från grunden. Så här skall en exempelkörning av programmet se ut:

    > gcc p6.c
    > ./a.out 40 12
    gcd(40, 12) = 4

Använd `printf()` för utskriften. Minns att `%d` är styrkoden för
heltal och `%s` är styrkoden för strängar.

**Tips på jämförelseoperatorer:**

```c
a == b // sant om a och b innehåller samma värde
a != b // sant om a och b inte innehåller samma värde
a < b  // sant om a:s värde är strikt mindre än b:s värde
a > b  // sant om a:s värde är strikt större än b:s värde
```

Boolesk algebra i C:

```c
!a     // sant om a är falskt
a && b // sant om både a och b är sanna
a || b // sant om a och/eller b är sanna/sant
```

Vi kan nu beskiva ytterligare C-operatorer i termer av de vi redan sett:

* `a <= b` är logiskt ekvivalent med `a < b || a == b`
* `a >= b` är logiskt ekvivalent med `a > b || a == b`
* `a != b` är logiskt ekvivalent med `!(a == b)` eller `a < b || a > b`
* `a == b` är logiskt ekvivalent med `!(a < b) && !(a > b)`


**Tips på sätt att manipulera numeriska variabler:**

* `a = a - 1` ändrar värdet på `a` till 1 mindre än vad det var innan
* `a -= 1` är ekvivalent med ovanstående
* `a--` och `--a` minskar värdet på `a` med 1 på samma sätt, men har subtila skillnader -- tills vidare bör du enbart använda dem för sido-effekter (om alls!)
* Motsvarande finns för addition `+=` och `++`
* `*=` och `/=` existerar även för multiplikation och division

**Frivilliga extrauppgifter:**

1. Detektera att programmet används korrekt -- exakt två positiva tal skickas in
2. Utöka programmet med stöd för hantering av negativa tal


## *Kontrollera om en sträng är ett tal (Skall redovisas)

Nu har det blivit dags för oss att skriva vår första funktion (förutom
`main()`-funktionen då) -- vilket vi kommer att ägna oss åt under nästa
labb. Vi skall skriva funktionen `is_number()` som tar emot en sträng
(`char *`) och returnerar en boolean (`bool`) -- `true` om den inskickade
strängen är ett tal, annars `false`.

Av historiska skäl måste stöd för booleaner inkluderas explicit i C på
följande sätt:

```c
#include <stdbool.h>
```

Genom detta bibliotek får du tillgång till datatypen `bool` samt
konstanterna `true` och `false`. (Nästan alla värden i C går att
konvertera till sanningsvärden, även om det ofta inte är
semantiskt vettigt. 0 är falskt och alla andra värden är sanna.
Konverteringen sker automatiskt, så `bool b = 1;` är logiskt
ekvivalent med `bool b = true;` även om det är vansinnig kod att
skriva.)

Skapa en ny fil `temp.c` med en tom `main()`-funktion med
kommandoradsargumenten i (du kan kopiera texten från högre upp på
denna sida). Inkludera `stdlib.h`, `stdio.h` och `stdbool.h` med
`#include`-direktivet. _Ovanför_ `main()`-funktionen, skriv in
följande:

```c
bool is_number(char *str)
{
  return false;
}
```

Du har nu deklarerat en funktion, `is_number()`, som tar emot en
sträng och returnerar ett sanningsvärde -- ett booleskt värde (aka
"en boolean"). Funktionens _kropp_ är just nu tom, så när som på
satsen `return false`, vilket innebär att funktionen alltid svarar
med falskt. Detta är en s.k. **stub**, dvs. en funktion vars
existens är explict men vars implementation ännu inte är skriven.
Den innehåller bara minimalt med kod för att den skall vara legal
enligt C-kompilatorn, och då är vi konservativa, dvs. ingen sträng
är ett tal. Som kropp i `main()` kan vi skriva följande:

```c
if (argc > 1 && is_number(argv[1]))
{
  printf("%s is a number\n", argv[1]);
}
else
{
  if (argc > 1)
  {
    printf("%s is not a number\n", argv[1]);
  }
  else
  {
    printf("Please provide a command line argument!\n");
  }
}
```

Pröva nu att kompilera och köra programmet:

    > gcc temp.c
    > ./a.out 42
    42 is not a number
    > _

Perfekt! Nu har vi något som "fungerar" men som gör fel, och
vår uppgift nu är att modifiera detta program tills det gör rätt.

**Det är viktigt att alltid ha ett fungerande program** så att det
går att experimentera sig fram till en lösning. Så arbetar såväl
nybörjade som experter -- ingen tycker att det är en bra idé att
skriva 10 rader kod mellan varje kompilering, även om värdet på 10
varierar mellan personer och ofta stiger något med erfarenhet med
den aktuella kodbasen.

En sträng i C är en array av tecken och varje tecken representeras
som ett heltal (ASCII-värdet för tecknet). Sist i en välformad
sträng kommer ett s.k. "nulltecken", som har värdet 0, och som
avser att "nu är strängen slut". Strängen `"Hej"` i C innehåller
alltså _4_ tecken: `['H', 'e', 'j', '\0']` (skrivet som en array av
teckenliteraler) eller `[72, 101, 106, 0]` (skrivet som en array av
ASCII-värden).

Ett enkelt sätt att kontrollera om en sträng är ett (hel)tal är
att inspektera om varje tecken i strängen är en siffa (0-9),
förutom det första tecknet som också kan vara ett minustecken `-`.

* Funktionen `strlen()` i biblioteket `string.h` (`#include <string.h>`) returnerar längden av en sträng (med eller utan nulltecknet? Utforska!)
* Funktionen `isdigit()` i biblioteket `ctype.h` testar om ett enskilt tecken är en siffra
* Implementera testet med hjälp av en loop från `i=0` till längden av strängen (utan nulltecknet)
* Minns att `str[42]` läser ut det 43:e tecknet från arrayen `str`

Nu har du nog med information för att skriva programmet! När du
fått det att fungera, kopiera funktionen (och import-satser) över
in i `p6.c` och använd funktionen för att kontrollera att
kommandoradsargumenten är heltal. Lägg också in en kontroll att de
inte är negativa (dvs. `talet >= 0`).

### Om funktioners ordning i filen

Som du har märkt har du blivit instruerad att placera funktioner
högre upp i filen än där de anropas. C-kompilatorn läser filen i
radordning, och om den inte först har sett en funktions
**deklaration** så kan den inte kontrollera att anropen till den
är korrekta, till exempel med avseende på antalet parametrar.
Redan i nästa labb skall vi se hur man kan komma runt detta med
så-kallade `header`-filer.

### Om return-satsen

Alla funktioner i C vars returtyp inte är `void` måste returnera
ett värde explicit med hjälp av `return`-satsen, varvid funktionen
omedelbart avbryts. Det är därmed tillåtet för en funktion att ha
flera `return`-satser utan att det blir tveksamt vad funktionen
returnerar. Även funktioner vars returtyp är `void` kan ha en "tom"
`return`-sats: `return;`. Detta avbryter funktionen men returnerar
inget värde.

Felaktigt användande av `return` kan leda till _död kod_, dvs. kod
som aldrig kommer att utföras, t.ex.:

:warning: **OBS!** _Illustrerar död kod -- skriv inte så här!_ :warning:
```c
int dead_code_example()
{
  return 17; // Här avbryts funktionen
  puts("This string will never be printed"); // denna rad körs aldrig
}
```

Det är viktigt att hitta död kod och ta bort den av flera skäl --
inte minst säkerhet!


# Extrauppgifter

För dig som är tidigt färdig eller känner att du vill arbeta mer
med materialet.

## Egen isdigit

Du kan implementera din egen `isdigit()` genom att kontrollera att
det inskickade tecknet `c` är `'0' <= c && c <= '9'`. Notera
skillnaden mellan `'0'` som är _tecknet_ '0', och `0` som är
_heltalet_ 0. Glöm inte att ta bort importen av `ctype.h` eller
döpa din funktion (t.ex. till `is_digit()`) så att namnet inte
krockar med `ctype.h`:s funktion.

Observera: du måste skriva din `isdigit()` _ovanför_ `is_number()`.

## Fibonacci

Skriv ett program `fib.c` som skriver ut de första _N_ talen i Fibonacciserien.
_N_ skickas in som ett kommandoradsargument som vanligt.

    > gcc fib.c
    > ./a.out 10
    0 1 1 2 3 5 8 13 21 34
    > _

Fibonacciserien definieras så här:

    fib(0) = 0
    fib(1) = 1
    fib(i) = fib(i-1) + fib(i - 2) om i >= 2

Som synes är definitionen av `fib()` rekursiv -- men vi skall lösa
den med hjälp av en loop. Använd två variabler `a` och `b` som
sätts till 0 respektive 1.

För att räkna ut `fib(3)`, utför följande beräkning i en loop:

1. räkna ut summan av `a` och `b`
2. sätt `a` till värdet på `b`
3. sätt `b` till summan i (1)
4. skriv ut `b`

För att räkna ut `fib(4)` kan vi fortsätta på samma sätt eftersom
`a` innehåller värdet på `fib(2)` och `b` innehåller värdet på
`fib(3)`, etc.

Generalisera detta i en loop så att det går att räkna ut
godtyckliga Fibonaccital.


## Heltalsvariablernas ändlighet

Här behandlas den "vita lögnen" ovan om "en typ för heltal [...]".

Hittills har vi använt typen `int` som en heltalsvariabel. Under
programmets körning sparas en `int` som ett binärt tal i ett
utrymme som är lika stort som ett _maskinord_, dvs. 32 eller 64
bitar beroende på vilken typ av dator man sitter på. Antalet bitar
styr (naturligtvis) hur stora tal som ryms i variabeln. En
32-bitars `int` har som maxvärde `2^31-1` och minvärde `-2^31`.

- Hur stor är en `int` på datorn du sitter på? Du kan pröva detta
  genom att lägga till `#include <limits.h>` överst i filen och
  sedan göra `printf("%d\n%d\n", INT_MIN, INT_MAX);`
- En `unsigned int` har endast positiva värden och
- Pröva vad som händer om du sparar ett för stort tal i en
  heltalsvariabel! (T.ex. genom att räkna ut ett för stort tal med `fib`-programmet.)

Datatypen `long` rymmer större tal (se `LONG_MAX`).

I modern C använder vi ofta datatyper vars storlek är garanterad
oavsett vilken plattform vi sitter på. Om du inkluderar `#include <stdint.h>`
i dina program får du tillgång till typer som:

* `int64_t` ett heltal som är garanterat att vara 64 bitar stort
* `uint64_t` ett "unsigned" heltal som är garanterat att vara 64 bitar stort (och alltså bara sparar positiva tal)
* `int8_t` ett heltal som är garanterat att vara 8 bitar stort
* etc.

Liknande gäller för flyttal. Analogt med `int` och `long` finns
`float` och `double`, samt ytterligare bibliotek för flyttalsberäkningar
enligt olika standarder.
