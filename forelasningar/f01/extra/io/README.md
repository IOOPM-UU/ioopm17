I/O
===

I/O står för "Input/Output", alltså in- och utmatning. I C och
Unix (och de flesta andra programmeringsspråk) sker all I/O med
hjälp av så kallade strömmar (*streams*). En ström kan ses som en
kanal som man kan skriva till eller läsa ifrån. Andra änden av en
ström kan vara en fil på hårddisken, ett annat program eller en
nätverks-socket.

## Standardströmmar

Det finns tre standardströmmar som är viktiga att känna till.
Dessa heter `stdin`, `stdout` och `stderr`. `stdin` är data som
går in i ett program, vanligtvis via terminalen. `stdout` är data
som kommer ut från ett program. Om man inte anger något annat så
sker alla utskrifter via `printf` och `puts` till `stdout`. Den
sista strömmen, `stderr`, används för att skriva ut
felmeddelanden. Vanligtvis går denna data också till terminalen,
men det kan finnas anledning att separera destinationen för
felmeddelanden och vanlig output (som då skrivs till `stdout`).

Nu ska vi titta på ett enkelt program som interagerar med
terminalen:

1. Öppna filen `io.c`. Det enda som borde vara nytt här är
  funktionen `scanf`, som används för att läsa från `stdin`. Dess
  första argument är en formatsträng, precis som den som `printf`
  tar emot. Formatsträngen `%s` betyder att vi kommer försöka
  läsa en sekvens av tecken tills vi stöter på ett blanktecken.
  Prova att kompilera och köra programmet. Det kommer att kräva
  inmatning i terminalen.

2. Nu ska vi lägga till information om användarens ålder. Deklarera
  en `int` som heter `age` i början av programmet. Lägg sedan till
  en fråga om personens ålder innan `printf`-anropet, följt av raden

  ``` c
    scanf("%d", &age);
  ```

  Och-tecknet innan `age` behövs för att `scanf` vill ha en
  minnesadress som argument. Formatsträngen `%d` säger att vi
  kommer försöka läsa ett heltal. Mer om det i nästa del! Utöka nu
  formatsträngen i `printf`-satsen med ett `%d` och lägg till
  `age` som argument. Kompilera och provkör!

3. Programmet funkar nu helt okej, men om man skriver in något som
  inte består av siffror som ålder så kommer programmet fortsätta ändå
  (och eventuellt ge konstiga utskrifter). Vi skulle vilja att
  programmet istället upprepade frågan om ålder om ett heltal inte
  gick att läsa.

  Vi kommer ta hjälp av att `scanf` returnerar ett värde som
  motsvarar hur många läsningar som lyckades. Om anropet
  `scanf("%d")` returnerar 1 lyckades funktionen läsa ett heltal,
  annars returnerar den 0. Vi skriver därför en loop som säger
  ungefär "Så länge som `scanf` inte lyckas läsa något heltal
  (alltså returnerar 0) så skriver vi ut en ny fråga":

  ``` c
    int count = scanf("%d", &age);
    while(count == 0){
      puts("Please use digits");
      count = scanf("%d", &age);
    }
  ```

  Notera att `count` **inte** är det inlästa heltalet, utan
  *antalet* heltal som `scanf` lyckades läsa.

4. Om du kompilerar och kör det här programmet och skriver in en
  felaktig ålder så kommer du märka att programmet fastar och bara
  skriver ut "Please use digits" om och om igen (använd `C-c C-c`
  för att avbryta körningen). Det är för att `scanf` inte tar bort
  det som den läser från `stdin`. `scanf` står alltså och försöker
  tolka samma felaktiga inmatning i all oändlighet!

  > "Definitionen av vansinne är att upprepa samma sak och varje gång förvänta sig ett annat resultat"

  Om inläsningen misslyckas måste vi se till att läsa förbi alla
  felaktiga tecken tills vi stöter på en radbrytning (varför just
  en radbrytning?). Vi utökar därför loopen till följande:

  ``` c
    int count = scanf("%d", &age);
    while(count == 0){
      puts("Please use digits");
      while(getchar() != '\n')
        ;
      count = scanf("%d", &age);
    }
  ```

  Funktionen `getchar` läser (och konsumerar) och returnerar ett
  tecken från `stdin`. Den inre `while`-loopen betyder alltså
  ungefär "Fortsätt att konsumera ett tecken i taget från `stdin`
  så länge som vi inte läser en radbrytning". Notera att den inre
  loopen inte har någon loop-kropp (bara ett `;`). Alla
  sidoeffekter ("läs ett tecken från terminalen") sker i loopens
  villkor.

  Nu ska programmet fungera som det ska! Du kan jämföra med
  `io_finished.c` om det inte gör det.

5. När man anropar ett program från terminalen kan man också
  omdirigera standardströmmarna till filer. Anropet `./io >
  out.txt` skickar allt som skrivs till `stdout` till filen
  `out.txt`. Notera att filen skrivs över om den redan finns!
  Anropet `./io < in.txt` kör programmet och läser `stdin` från
  filen `in.txt`. Man kan också kombinera dessa kommandon. Prova
  att skapa en fil som heter `in.txt` med innehållet

  ```
  Silvia
  xyz
  69
  ```

  och kör med kommandot `./io < in.txt > out.txt`. Undersök
  innehållet i `out.txt` med `cat`.

## I/O till filer

Även om man kan göra en del med bara omdirigering så är det
praktiskt att kunna öppna filer för läsning och skrivning direkt i
själva programmet. Som exempel ska vi skriva ett program som läser
in en fil och skriver ut den till en annan fil, fast med
radnummer.

1. Ett skelett till programmet finns i `linum.c`. Programmet läser
   det första av sina argument vid terminalanropet som ett filnamn
   (variablen `infile`), och skapar en sträng som är filnamnet
   fast med `"lin_"` före (variabeln `outfile`). Notera att
   längden på `outfile` är längden av av `infile` plus *fem* - de
   fyra tecknen i `"lin_"` och det avslutande `\0`-tecknet.

   De nästföljande två raderna öppnar strömmen `in` som en
   *läsström* från `infile`, och strömmen `out` som en
   *skrivström* till `outfile`. Funktionen `fopen` används i båda
   fallen, men vilket läge som avses (läsning eller skrivning)
   anges med det andra argumentet. En ström har typen `FILE*`.

   I slutet av programmet stängs båda strömmarna, vilket är
   viktigt för att undvika korrupta filer och för att se till att
   programmet frigör alla resurser det har allokerat.

2. Om du kompilerar och kör programmet (med en fil som argument)
   så kommer bara en ny tom fil med prefixet `"lin\_"` skapas. Vi
   ska nu skriva kod som läser från strömmen `in` och skriver till
   strömmen `out`, och vi skriver koden på det markerade stället.

   Vi kommer behöva två hjälpvariabler. En `int` som håller koll på
   vilket radnummer vi är på, och en sträng som kan lagra en inläst rad
   i taget:

   ``` c
     int line = 1;
     char buffer[128];
   ```

   Stränglängden 128 är godtycklig. Det viktiga är att en hel rad
   från filen vi läser får plats i `buffer`.

3. För att läsa rader från `in` använder vi funktionen `fgets`.
   Anropet `fgets(buffer, 128, in)` läser en sekvens av tecken
   från strömmen `in` tills den stöter på en radbrytning, eller
   som mest `127` tecken, och lagrar dem i strängen `buffer`
   (jämför med `strncpy` från
   [extramaterialet om strängar](../strings)). Radbrytningstecknet (om
   det hittades innan `127` tecken) kommer med i strängen.

   Vi kommer vilja utföra samma sak för varje rad i filen som `in`
   pekar på. `fgets` returnerar `NULL` när strömmen den läser
   ifrån tar slut och det inte finns något mer att läsa. Det här
   kan vi använda för att skriva en while-loop med villkoret "Så
   länge som `fgets` lyckas läsa in en rad till `buffer`":

   ``` c
       while(fgets(buffer, 128, in) != NULL){ ... }
   ```

4. Inuti loopen har `buffer` precis fyllts med en rad från från
  `in` (om villkoret i loopen var sant, har anropet till `fgets`
  precis lyckats). För att sedan skriva ut strängen med radnummer
  använder vi `fprintf` som fungerar precis som vanliga `printf`
  förutom att den också tar strömmen den ska skriva till som
  argument (innan formatsträngen). Slutligen ökar vi på radnumret
  med ett inför nästa loop. Nu borde loopen se ut så här:

  ``` c
  while(fgets(buffer, 128, in)){
    fprintf(out, "%d. %s", line, buffer);
    line++;
  }
  ```

5. Spara en ny fil med tre fyra rader text som `test.txt` och
   provkör programmet med kommandot `./linum test.txt`. Titta sen
   på resultatet i `lin_test.txt` med `cat`. Prova också
   programmet på någon kodfil som du har skrivit!

6. Slutligen kan det vara intressant att se vad som händer om man
   allokerar en för liten sträng att lagra raderna i. Prova att
   minska storleken på `buffer` till 5 och kompilera om programmet
   igen. Kör det på en fil som har rader längre än fyra tecken. Vad
   blir resultatet?

Det är värt att poängtera att vi hade kunnat skriva programmet
`linum` med hjälp av omdirigering av `stdin` och `stdout`. En
frivillig utvidgning av uppgiften är att låta programmet använda
standardströmmarna när man inte ger det något argument, så att man kan
anropa det både som `./linum test.txt` och `./linum < test.txt > lin_test.txt`.

### Att ta med sig

* In- och utmatning sker med hjälp av strömmar som har typen
  `FILE*`.
* Standardströmmarna `stdin`, `stdout` och `stderr` är kopplade
  till terminalen (om inget annat anges). Funktioner som inte tar
  någon ström som argument läser och skriver i allmänhet via
  `stdin` och `stdout`.
