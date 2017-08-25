# Labb 5: mer I/O och utökning av `db.c`

:warning: **OBS!** I slutet av den här labben ska du ladda upp
dina resultat på GitHub. **Glöm inte att göra det!** :warning:

Hittills har vi talat om att läsa och skriva till och från
terminalen. Lyckligtvis är en grundläggande abstraktion kring I/O
i C baserad på filer -- oavsett om vi skall läsa från
tangentbordet eller från en plats på hårddisken.

Följande program läser tecken för tecken från s.k. `stdin` som är
en fil som normalt är knuten till terminalen i våra C-program.
`stdin` motsvarar helt enkelt inläsning från tangentbordet.

Skrivning sker analogt till `stdout` och allt som skrivs dit visas
i terminalen i våra program.

```c
/// passthrough.c
#include <stdio.h>

int main(void)
{
  int c = getchar();
  int safety = 1024;

  while (c != EOF && --safety > 0)
  {
    putchar(c);
    c = getchar();
  }

  return 0;
}
```

Detta program läser max 1024 gånger från `stdin` och skriver
det som lästes på `stdout`. Så här kan en körning se ut:

    > gcc passthrough.c
    > ./a.out
    hej               <-- input
    hej               <-- skrivs ut
    hopp i galopp     <-- input
    hopp i galopp     <-- skrivs ut
    ^C                <-- ctrl+c för att avbryta
    >

Med hjälp av `|` kan du tala om att output från ett program skall
skickas till ett annat (på Linux och OS X):

    > gcc passthrough.c
    > head -n 3 passthrough.c   # skriver ut första 3 raderna i passthrough.c
    /// passthrough.c
    #include <stdio.h>

    > head -n 3 passthrough.c | wc -l   # räkna antalet rader i input
    3
    > head -n 3 passthrough.c | ./a.out
    /// passthrough.c
    #include <stdio.h>

Observera att när vi skickade output från `head` till `a.out` (vår
kompilerade `passthrough.c`) så skrevs den ut igen, precis som om vi
hade skrivit in den via terminalen.

Programmet vet alltså inte om om det läser från en fil eller från ett
annat program.

Här är några hjälpfunktioner för att explicit läsa från en fil
inifrån C (istället för att skicka in den utifrån som ovan):

* Funktionen `fopen()` tar som input två strängar -- den första är
  filnamnet och den andra beskriver hur filen skall öppnas. För
  läsning: `"r"`, för skrivning `"w"`, och `"a"` för append.
  `fopen()` returnerar en `FILE *` -- dvs. en pekare till en fil
  som kan användas för att läsa från/skriva till beroende på hur
  filen öppnades (`"r"`, etc.).
* `fclose()` stänger en öppen fil.
* `fprintf()` fungerar som `printf()` men är inte låst till `stdout`
  -- `printf(...)`  är ekvivalent med `fprintf(stdout, ...)`. Alltså,
  `fprintf(fil, ...)` skriver ut på filen `fil`.
* `fgetc(fil)` läser ett tecken från filen `fil`.
* `fscanf(fil, ...)` läser som `scanf()` fast från filen `fil`.
* etc.


## Uppvärmning: Cat med radnumrering

Nedan följer en version av programmet `cat` som läser en fil och
skriver ut filen på terminalen (`stdout`). Programmet är väldigt
likt `passthrough.c` ovan -- med skillnaden att vi vill öppna en
namngiven fil, inte `stdin`:

```c
/// cat.c
#include <stdio.h>

void cat(char *filename)
{
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);

  while (c != EOF)
  {
    fputc(c, stdout);
    c = fgetc(f);
  }

  fclose(f);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      cat(argv[i]);
    }
  }

  return 0;
}
```

(observera att detta program inte fungerar så bra om vi anger filer som inte finns -- men det är inget du behöver fixa.)

Titta på programmet ovan: i funktionen `cat()` läser vi infilen
tecken för tecken. Nu vill vi skriva ut filen så att varje rad
börjar med ett radnummer. Här är ett exempel från texten i labben:

    1   Titta på programmet ovan: ...
    2   tecken för tecken. Nu vill ...
    3   börjar med ett radnummer ...

**Ledning:**

* Ha en räknare för antalet rader i `cat()` som börjar på 1
* Skriv ut 1 innan vi går in i loopen i `cat()`
* Tecknet `'\n'` är radslutsteckenet -- efter varje sådant tecken kommer en ny rad
  * Inkrementera räknaren
  * Skriv ut räknaren


**Uppvärmning: Frivilliga utökningar av cat**

1. Utöka programmet så att när flera filer skrivs ut (stöds redan) börjar radräknaren _inte_ om från 0 vid varje ny fil
2. Innan varje fil skrivs ut, skriv ut `==== filnamn.ext ====` i terminalen
3. Skriv om `cat.c` till `cp.c` och låt programmet kopiera från en fil till en annan, tecken för tecken, analogt med programmet `cp`


## Slutprojektet på labbarna: Utökning av databasen

Nu skall vi avsluta vår implementation av databasprogrammet. I en
senare inlämningsuppgift skall vi utöka databasen med stöd för att
spara och ladda databasen på fil med hjälp av funktionerna ovan
(och andra), men det är lite för tidigt ännu. Istället skall vi
utöka programmet med en interaktiv meny, och stöd för insättning
och borttagning.


### Menyfunktionalitet 1/2

Vi skall utöka programmet med en meny med olika val:

    [L]ägga till en vara
    [T]a bort en vara
    [R]edigera en vara
    Ån[g]ra senaste ändringen
    Lista [h]ela varukatalogen
    [A]vsluta

Skriv en funktion `print_menu()` som skriver ut ovanstående text
på `stdout`.

Guldstjärna för att göra utskriften med endast en enda `puts()`
eller `printf()` utan att göra utskriftssträngen oläslig.


### Menyfunktionalitet 2/2

Skriv en funktion `ask_question_menu()` som skriver ut menyn
med `print_menu()` och sedan låter användaren mata in sitt val.

Funktionen skall kontrollera att resultatet som användaren matar
in är giltigt (följande tecken `LlTtRrGgHhAa`) och fråga om tills
ett giltigt val gjorts. Funktionen skall returnera valet som ett
enda tecken (en `char`) som skall vara en stor bokstav. Funktionen
`toupper()` i `ctype.h` kan användas för att konvertera en gemen
till en versal.

**OBS:** Om du vill kan du använda din generiska
`ask_question()`-funktion. Du måste skriva en ny kontrollfunktion
from kontrollerar att input är ett tecken i strängen
`"LlTtRrGgHhAa"`, och antingen utöka `answer_t` eller låta tecknet
vara ett heltal. Om du gör på detta vis behövs inte
`print_menu()`-funktionen längre, eller så kan du använda denna
funktion för att returnera strängen som skall skrivas ut. (OBS!
Inget `strdup()` i denna funktion i så fall!)


### Tillägg i databasen

Skriv en funktion `add_item_to_db()` som lägger till en vara i
databasen med `input_item()` från föregående labb. Du kan
förutsätta att det finns plats i databasen.

* Vad skall funktionen ta som input?
* Vad skall funktionen returnera?


### Borttag ur databasen

Skriv en funktion `remove_item_from_db()` som tar bort en vara
från databasen. Använd `list_db()` för att skriva ut databasen och
samma metod som vid `edit_db()` för att välja vilken vara som
skall tas bort.

När man tar bort något ur en array måste man "skriva över" det man
vill ta bort med elementen till höger. Dvs. ponera arrayen _A_ med
elementen `[1, 2, 3, 4]`. Variabeln _as_ håller reda på antalet
element i _A_ och är just nu 4.

Om jag vill ta bort 1:an kan jag göra det genom att kopiera 2:an
till 1:ans plats, 3:an till 2:ans plats och så vidare. Det betyder
att det kommer att finnas två 4:or sist i arrayen --
`[2, 3, 4, 4]` -- men om jag också minskar _as_ till 3 och
respekterar detta kommer jag inte att läsa den andra fyran. Vid
insättning skrivs den över och _as_ ökar till 4. Motsvarigheten
till _A_ i vårt program är förstås `db` och _as_ `db_siz`.

Kopieringen sker lämpligen från höger till vänster. Notera att om
jag i ovanstående exempel ville ta bort 4:an räcker det med att
bara miska _as_ med 1. Om jag ville ta bort 3:an räcker det med
att kopiera över 3:an med 4:an, lämna 1 och 2, och minska _as_ med 1.


### *Integration (Skall redovisas)

Skriv en funktion `event_loop()` som anropar `ask_question_menu()`
och baserat på svaret antingen `add_item_to_db()`,
`remove_item_from_db()`, `edit_db()`, `list_db()` för
motsvarande menyval. För ångra-valet skall ett meddelande `Not yet
implemented!` skrivas ut. Och vid avsluta skall `event_loop()`
funktionen terminera och programmet avslutas.

### Utökad vara

Utöka definitionen av en vara till att också ha ett antal
(`amount`) som avser hur många av en vara som lagrats på
lagerhyllan. Hur går du tillväga för att utöka programmet? Kan C:s
kompilator hjälpa dig på något sätt?


### Frivilligt: stöd för ångra

Implementera stöd för att ångra. Detta omfattar:

1. Vid borttagning, spara det som togs bort
2. Vid redigering, spara originalet
3. Vid insättning, spara vilken vara som lades till
4. Spara alltid vilken som var den senaste handlingen som kan
   ångras -- du kan t.ex. använda ett heltal för att hålla koll på
   vad det var för typ av handling (den mest eleganta lösningen
   involverar funktionspekare)
5. När användaren väljer ångra, inspektera vilken handling som var
   den senaste, och ångra den
6. Om du vill kan du implementera stöd för att ångra själva ångrandet

## *Ladda upp alla dina labbar på GitHub

Du borde ha fått ett GitHub-konto från oss på en adress som liknar
`https://github.com/IOOPM-UU/fornamn.efternamn.1234`, där
`fornamn.efternamn.1234` är ditt student-ID (om du inte har fått
det,
följ [dessa instruktioner](http://wrigstad.com/ioopm/github.php)).
Här ska du ladda upp alla uppgifter som du har redovisat under de
här veckorna. Det finns många sätt att ladda upp filer till
GitHub, och här går vi igenom ett sätt att göra det via
terminalen.

1. Klona ditt repo (om du inte redan har gjort det):

   ```
   > git clone https://github.com/IOOPM-UU/fornamn.efternamn.1234
   ```

   Detta skapar en mapp som heter `fornamn.efternamn.1234` som du
   kan synka med online-versionen på GitHub. Du kan döpa mappen
   till vad som helst och lägga den var du vill.

2. Kopiera eller flytta över filerna som behövs för att kompilera
   och köra dina labbar i respektive mapp. Till exempel bör
   `labbar/lab2` innehålla `guess.c`, `utils.c` samt `utils.h`. Om
   du har sparat dina gamla labbar i en mapp som heter `ioopm` som
   ligger i samma mapp som ditt klonade repo kan du köra:

   ```
   > cp ioopm/lab2/guess.c fornamn.efternamn.1234/labar/lab2/
   > cp ioopm/lab2/utils.c fornamn.efternamn.1234/labar/lab2/
   > cp ioopm/lab2/utils.h fornamn.efternamn.1234/labar/lab2/
   ```

3. För varje labb, gå till respektive mapp och markera att du vill
   synka dessa med kommandot `git add`. Bunta sedan ihop
   ändringarna till en "commit" med commandot `git commit`. Till
   exempel:

   ```
   > cd fornamn.efternamn.1234/labbar/lab2
   > ls
   README.md    utils.c
   guess.c      utils.h
   > git add guess.c
   > git add utils.c
   > git add utils.h
   > git commit -m "Lade till labb 2"
   ```

   Flaggan `-m` används för att ge en beskrivande text till en
   commit.

4. Slutligen, synka online-versionen med din egen version genom
   att "knuffa upp" dina ändringar (alltså dina commits) med
   kommandot `git push`. Nu ska du kunna se ändringarna på GitHub!

Om du vill lära dig mer om Git och GitHub finns det många guider
online. Du hittar några av dem i
vårt [länkbibliotek](http://wrigstad.com/ioopm/links.php#git). Det
finns också
en [kortare lathund](../extramaterial/lathundar/github) med de
vanligaste Git-kommandona, baserad på en tidigare IOOPM-students
anteckningar.
