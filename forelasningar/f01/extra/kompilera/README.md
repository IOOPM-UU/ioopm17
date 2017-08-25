Kompilera ett C-program
=======================

1. Ett C-program består av en eller flera källkodsfiler. Filer
  med ändelsen .c innehåller körbar kod medan filer med ändelsen
  `.h` (header-filer) normalt endast innehåller deklarationer och
  metadata om programmet. Vi kommer att använda oss av båda dessa
  under kursen, men initialt fokuserar vi på `.c`-filerna.

  Vid kompilering översätts en eller flera källkodsfiler till
  **objektkod** som är ett mellansteg på vägen till ett körbart
  program. Objektkodsfiler innehåller maskinspecifika
  instruktioner skapade från källkoden, men för att bli körbara
  måste dessa **länkas** samman med varandra och de
  maskinspecifika standardfunktioner som programmet använder.
  Kompilering och länkning är två olika steg, men vi kommer i
  regel att utföra dem direkt efter varandra så att de framstår
  som ett enda.

  Under kompileringssteget försöker kompilatorn identifiera fel i
  källkoden (t.ex. du anropar funktionen $f$ med för få argument).
  Under länkningen uppstår fel om inte alla beroenden är lösta
  (t.ex. du anropar en funktion $f$ men det finns ingen sådan
  funktion). En anledning till att ett beroende inte är löst är
  att man kanske stavat fel till $f$ alternativt att man glömt att
  inkludera den fil som innehåller $f$ i sin kompilering.

  I denna uppgift skall vi steg för steg bygga upp en
  "trollformel" som med fördel kan användas för all kompilering
  under denna sprint. Programmet som vi skall kompilera ligger i
  den här mappen och heter `passbyval.c`. 


2. Kompilera programmet med hjälp av C-kompilatorn GCC:

  ```
  foo> gcc passbyval.c
  ```

  Du får nu kanske ett felmeddelande `error: 'for' loop initial
  declaration used outside C99 mode`. Detta felmeddelande får du
  för att koden använder sig av den C-standard som fastslogs 1999
  ([en ny C-standard fastslogs 2011](http://en.wikipedia.org/wiki/C11_%28C_standard_revision%29),
  och den kommer vi att använda på kursen). Du måste ange explicit
  att du vill tillåta sådana "moderna features":

  ```
  foo> gcc -std=c11 passbyval.c
  ```

  Nu bör koden kompilera som den skall.

3. Gör `ls -l` för att lista innehållet i den nuvarande
  katalogen. Lägg märke till filen `a.out` -- det är det
  kompilerade programmet. Du kanske är van från OSX att körbara
  program har filändelsen ".app" eller från Windows, ".exe"?
  Om man inte explicit anger ett namn på det kompilerade
  programmet får det namnet `a.out`, och körs så här (kör
  inte ännu!):

  ```
  foo> ./a.out
  ```

  Notera att vi vill att du anger `./` vilket betyder "i denna
  katalog", vilket hindrar att du råkar köra ett annat program som
  heter `a.out` som ligger någonstans i din path (Miljövariabeln
  `PATH` avgör var terminalen ska leta efter program. Kommandot
  `echo $PATH` skriver ut dess värde) och som därför inte
  nödvändigtvis gör det du vill.

4. Kompilera om programmet och döp den exekverbara filen till
  `passbyval`:

  ```
  foo> gcc -std=c11 -o passbyval passbyval.c
  ```

5. Normalt när vi kompilerar vill vi att kompilatorn skall vara
  maximalt känsligt för eventuellt knas och vi vill därför slå på
  "alla varningar":

  ```
  foo> gcc -std=c11 -Wall -o passbyval passbyval.c
  ```

6. Vidare vill vi slå på maximalt stöd för debuggning, och
  eftersom vi använder gcc skall vi speciellt dra nytta av
  "gdb", GNUs debugger:

  ```
  foo> gcc -std=c11 -Wall -ggdb -o passbyval passbyval.c
  ```

  Nu har vi kommit fram till den "trollformel" som, med undantag
  för namnet "passbyval", är den ramsa du kommer att upprepa vid
  varje kompilering av ett enkelt program.

7. Om ditt program består av flera källkodsfiler som skall byggas
  till en enda exekverbar fil kan du ange samtliga dessa filer
  direkt vid kompilering:

  ```
  foo> gcc -std=c11 -Wall -ggdb -o passbyval passbyval.c more.c another.c etc.c
  ```

  Lägg på din att-göra-lista att se på våra screencasts om
  separatkompilering och makefiler som tar kompilering till nästa
  nivå.

8. Nu är det dags att köra programmet (det kanske du redan har
  gjort). Du kommer då att märka att det inte gör rätt. Det är
  avsiktligt -- det leder oss nämligen in på nästa ämne:
  [debuggning](../debuggning).

### Att ta med sig:

* Kompilatorn är din vän, och den hittar många dumma fel -- men inte alla
* Kompilera **ofta** för att minimera mändgen felutskrifter vid varje givet tillfälle, och slå på maximalt med varningar för att fånga alla fel
* Om du får varningar eller kompileringsfel -- se till att alltid åtgärda dem innan du "fortsätter"
* Kompileringsfelen skall läsas uppifrån och ned!
