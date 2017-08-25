# Föreläsning 6

* [Bilder](f6.pdf)

## Make

Filerna `greeter.c`, `util.c`, `util.h`, `person.c`, `person.h`
och `tester.c` används för att exemplifiera separatkompilering med
hjälp av make. `Makefile` innehåller förklarande kommentarer om
hur den funkar (sådana behöver man förstås inte skriva själv).
Utgå gärna från den när du skriver egna makefiler!

Följande regler finns i `Makefile`:

* `make greeter` - bygg programmet `greeter`
* `make tester` - bygg programmet `tester`
* `make test` - bygg och kör `tester` med `test_in.txt` som
  `stdin`
* `make person.o` och `make asker.o` - kompilera respektive
  objektfil
* `make all` - bygg programmen `greeter` och `tester`
* `make clean` - städa bort alla filer som skapats av makefilen

## `gdb`

I mappen [gdb](gdb) finns tre program som alla innehåller buggar
(du kan bygga dem med `make all`):

* `fact` ska räkna ut fakulteten för sitt argument och skriva ut
  det. Här kan det finnas flera buggar!
* `calc` ska utföra avancerade (läs meningslösa) beräkningar i en
  array och skriva ut resultatet.
* `db` är en uppgift från tidigare kursinstanser och är ett
  exempel på hur man inte ska skriva kod. Kör programmet med `make
  run` och prova att ta bort något ur databasen...

Försök använda `gdb` för att lista ut var buggarna är och hur de kan
åtgärdas. Notera att programmet `lldb` används på vissa
plattformar istället för `gdb`. Här är några användbara kommandon:

* `run` eller `r` kör programmet. Om programmet kräver argument
  (som `fact` och `db` ovan) skriver man dessa efter `run`.
* `b foo` sätter en *breakpoint* i `foo` så att programmet stannar
  när `foo` anropas. `b main` är bra om man vill stega igenom
  programmet från början.
* `b foo.c:42` sätter en breakpoint på rad 42 i `foo.c`. Om
  programmet redan är i `foo.c` räcker `b 42`.
* `step` eller `s` går ett steg i programmet.
* `next` eller `n` går till nästa rad i programmet (och hoppar
  förbi eventuella funktionsanrop)
* `continue` eller `c` kör programmet till nästa breakpoint.
* `print` eller `p` skriver ut en variabel eller minnesadress.
* `disp` skriver ut en variabel efter varje steg.
* `bt` skriver ut programmets *backtrace*, alltså kedjan av
  funktionsanrop som ledde till den nuvarande punkten i körningen.
* `up` flyttar uppåt i anropskedjan (till den som anropade
  funktionen man står i).
* `down` flyttar nedåt i anropskedjan (till den funktion som
  anropats från den man står i).
* Du kan använda `C-c` för att stanna en körning mitt i (praktiskt
  om programmet fastnat i en loop till exempel).

# Vad du kan göra själv

Förutom att leta buggar i programmen ovan så är det bästa sättet
att lära sig verktyg som `gdb` och `make` att använda dem själva.
Från och med nu:

* Ha **alltid** makefiler till dina projekt. Utöka dem när det
  tillkommer filer. Använd dem (åtminstone) för att kompilera,
  köra tester och städa upp dina genererade filer. Kommer du på
  något som du gör ofta via terminalen? Skriv en regel för det!

* Använd **alltid** `gdb` när du har en bugg i ditt program,
  framförallt om det är en krasch. Det räcker oftast med att köra
  programmet utan breakpoints för att få veta exakt på vilken rad
  som programmet kraschar och vilka värden som ligger i
  programmets minne just då.