**OBS!!** Om du känner dig stressad -- börja med den fråga som du skall redovisa och hoppa över resten av labben och spara den till senare! **OBS!!**

# Labb 4: Del 1 -- pekare

Pekare -- adresser till platser i minnet där data är lagrat -- är
en viktig del av C-programmering. Genom att dela information
mellan funktioner om _var_ något är lagrat sker två saker:

1. mottagaren kan **läsa** datat på platsen
2. mottagaren kan **ändra** datat på platsen

Att skicka platsen där datat finns istället för att skicka själva
datat kan vara väldigt effektivt. Om funktion _A_ har en array med
10 miljoner skivspår och vill att funktion _B_ skall hitta antalet
förekomster av "Kaffe utan grädde" skulle tiden för att kopiera 10
miljoner skivspår förmodligen vara betydligt högre än kostnaden
för sökningen. Genom att _dela med sig_ av datat via en pekare
istället för att kopiera hela rasket blir programmet mycket mer
effektivt.

Den stora **risken** med pekare ligger bland annat i att _B_ också
får rätt att ändra i datat (det går ibland att lösa med hjälp av
nyckelordet `const` som vi skall se senare) -- och att det inte
finns något sätt för implementatören av _A_ att veta att _B_
faktiskt inte modifierar datat, förutom att läsa all kod i _B_
(inklusive koden för alla funktioner som _B_ anropar).


## Värdesemantik vs. pekarsemantik

Vad skriver detta program ut på skärmen när det körs?

1. 7, 42
2. 42, 7
3. Något annat

```c
// Program 1

#include <stdio.h>

void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

int main(void)
{
  int x = 7;
  int y = 42;
  swap(x, y);
  printf("%d, %d\n", x, y);
  return 0;
}
```

Om det råder minsta tvekan -- kör programmet!

Programmet exemplifierar *värdesemantik*, dvs. att vid anrop
överförs argumentens värde genom **kopiering**. `a` och `b` i
`swap()` har samma värde som `x` respektive `y` initialt, men
förändringar av `a` och `b` påverkar inte `x` och `y`.


## Skriv om `swap()` med pekarsemantik

Namnet `swap()` i programmet ovan är misledande -- det antyder
något som i programmet ovan inte stämmer. Nu skall vi skriva om
`swap()` så att det använder pekare istället. Det påverkar typerna:

    int  a  // a är en variabel som innehåller ett heltal
    int *b  // b är en variabel som innehåller en adress till en plats i minnet där det finns ett heltal

Variabeln `b` ovan innehåller alltså en adress. För att komma åt
det heltal som ligger på den adressen skriver vi `*b`. Vi säger
att vi **avrefererar** `b`. Vi har tidigare sett **adresstagningsoperatorn**
`&` som vi kan använda för att få platsen i minnet där något data finns.
Vi kan t.ex. skriva `&a` för att avse platsen där `a`:s värde finns lagrat.
Om `a` och `b` är deklarerade enligt ovan kan vi skriva:

    a = 42;  // a innehåller nu heltalet 42
    b = &a;  // b innehåller nu en adress till där värdet på a finns lagrat
    printf("%d, %d\n", a, *b);  // skriver ut 42, 42
    a = 7;
    printf("%d, %d\n", a, *b);  // skriver ut 7, 7
    *b = 42;
    printf("%d, %d\n", a, *b);  // skriver ut 42, 42

Med hjälp av pekartypen `int *`, adresstagningsoperatorn `&` och
avrefereringsoperatorn `*` kan vi nu skriva om `swap()` så att
funktionen tar in två **pekare** (aka adresser) till heltal, och
byter plats på värdena som finns lagrade på dessa två platser.
Målet är att skriva om Program 1 ovan så att `42, 7` skrivs ut när
det körs.

Ledning:

1. Signaturen för `swap()` skall vara`void swap(int *a, int *b)`
2. Du kommer att använda avrefereringsoperatorn i implementationen av `swap()`
3. Du måste använda adresstagningsoperatorn i `main()` för att kunna anropa `swap()` (detta är enda ändringen du skall göra i `main()`)


## Mer om pekare och arrayer

Vi har sett att C:s strängtyp är `char *` och att en sträng är en
array av tecken. Ovan såg vi att `int *` betyder pekare till en
`int`. Hur kan en sträng vara både en pekare och en array? Är inte
det typvidrigt?

*Skillnaden mellan arrayer och pekare i C är extremt liten, och
tillsvidare kan vi betrakta pekare och arrayer som samma sak.*

Typerna `t *` och `t[]` är i regel utbytbara, för varje typ `t`.
Det betyder t.ex. att `char *argv[]` också kan skrivas `char
**argv`. Ovan sade vi att `int *` betyder en pekare till en plats
i minnet där det finns **ett** heltal. Det var en vit lögn -- det
borde vara "där det finns ett eller flera heltal."

Arrayer i C överförs med pekare, dvs. när man skickar en array
från en funktion till en annan skickas inte en kopia av arrayen
utan bara själva adressen till den. Att det är så är inte så
konstigt om man betänker att arrayer i C inte känner till sin egen
längd (jmf. strängar vars längd vi måste räkna ut genom att räkna
antal tecken fram till `'\0'`). C kan alltså inte själv räkna ut
hur många bytes som skall kopieras när man kopierar en array, så
det enda alternativ som återstår är att överföra pekaren istället.

**Pekararitmetik** är aritmetik som innefattar adresser. Om `a`
har typen `int *` pekar `a` på ett heltal och `a + 1` på "nästa
heltal". Uttrycket `a + 1` skapar en ny adress från adressen i
`a`. Observera att `a + 1` **alltid** kan beräknas, oavsett om det
finns något "nästa heltal" eller inte -- analogt med att C inte
vet längden på en array och därmed inte kan förhindra åtkomst till
element 26 i en array med bara 20 element. Det är helt enkelt
något som programmeraren måste sköta själv!

Många program som manipulerar arrayer kan skrivas om på ett
kortare sätt med pekararitmetik. Här är t.ex. funktionen
`string_copy()` som kopierar en sträng till en annan (kopierar
alla tecken från en array av tecken till en annan):

```c
void string_copy(char *source, char *dest)
{
  while (*dst++ = *source++) ;
}
```

En bättre (mer lättläst) version:

```c
void string_copy(char *source, char *dest)
{
  while (*source)
  {
    *dest = *source;
    ++dest;
    ++source;
  }
}
```

Eller med en `for`-loop (där iterationsvillkoret har blivit tydligare):

```c
void string_copy(char *source, char *dest)
{
  for (; *source != '\0'; ++dest, ++source)
  {
    *dest = *source;
  }
}
```

För att illustrera pekararitmetik ytterligare kan vi skriva om
`string_length()` från labb 3 så här:

```c
int string_length(char *str)
{
  char *end = str;
  while (*end != '\0') ++end;
  return end - str;
}
```

Förklaring:

1. `end` pekar från början på starten av strängen, precis som `str`
2. Så länge som tecknet som `end` pekar på (dvs. `*end`) inte är `'\0'`, flytta `end`-pekaren till nästa tecken
3. Längden på strängen är "avståndet" mellan `end` och `str` när `end` pekar på strängens nulltecken


## Skriv om `print` från labb 3 med pekare istället för array-index

```c
void print(char *str)
{
   ...
}
```

Använd `str` som en pekare och använd inte array-indexering
(alltså inte `str[12]`).

**Ledning:** Vi kan implementera `trim()`-funktionen från labb 3 på
motsvarande sätt:

```c
char *trim(char *str)
{
  char *start = str;
  char *end = start + strlen(str)-1;

  while (isspace(*start)) ++start;
  while (isspace(*end)) --end;

  char *cursor = str;
  for (; start <= end; ++start, ++cursor)
    {
      *cursor = *start;
    }
  *cursor = '\0';

  return str;
}
```

# Labb 4: Del 2 -- struktar

**Struktar** är grupperingar av värden. En strukt-deklaration skapar
en ny typ som kan användas i ett C-program.

En strukt deklareras precis som en **union** men använder
nyckelordet **strukt** istället:

```c
struct point
{
  int x;
  int y;
};
```

Strukten `point` innehåller två **fält** (aka poster, inbland
medlemmar eller medlemsvariabler), `x` och `y` -- båda av
heltalstyp. Ett värde av `point`-typ, "en point", grupperar alltså
två värden som hör ihop, i detta fall x- och y-koordinaterna hos
en punkt. På så vis kan man skicka runt en punkt mellan funktioner
som ett sammanhållet värde, istället för att skicka en massa "lösa
variabler". Ponera t.ex. att du skulle vilja skapa en rektangel
från två punkter -- fyra koordinater. Om du inte grupperade dem
som punkter måste du komma på något system för att veta vilken
x-koordinat som hör ihop med vilken y-koordinat.

Den närmsta motsvarigheten till struktar i Haskell är definitionen
av nya datatyper:

```haskell
data Point = Point {x :: Int, y :: Int}
```

Struktar i C har värdesemantik -- dvs. överförs med kopiering. Så
här kan man skapa (och skriva ut) en strukt:

```c
struct point p;
p.x = 10;
p.y = -42;

printf("point(x=%d,y=%d)\n", p.x, p.y);
```

Klistra in ovanstående i ett tomt program tillsammans med
`struct`-deklarationen av `point` och kör programmet. En smidig
syntax för att skapa struktar med initialvärden finns -- här är
samma program skriven med hjälp av denna:

```c
struct point p = { .x = 10, .y = -42};

printf("point(x=%d,y=%d)\n", p.x, p.y);
```

Ofta använder man en `typedef` för att definiera ett typalias
som inte innehåller det extra `struct`-nyckelordet:

```c
typedef struct point point_t;
```

Nu är `struct point` och `point_t` synomyma och vi kan skriva
vårt program så här:

```c
point_t p = { .x = 10, .y = -42};

printf("point(x=%d,y=%d)\n", p.x, p.y);
```

Värt att notera med `{ .x = 10, .y = -42 }`-syntaxen är att det är
tillåtet att **utelämna** fält som då får defaultvärden enligt följande:

1. heltalsfält får värdet 0
2. flyttalsfält får värdet 0
3. booleska fält fär värdet false
4. pekarfält får värdet `NULL` som betyder att de ännu inte pekar ut något -- vi skall återkomma till `NULL` senare

Följande program är alltså legalt (kör det gärna för att verifiera
att din uträkning av vad det skriver ut stämmer):

```c
point_t p1 = { .x = 10 };
point_t p2 = { .y = -42 };
point_t p3 = { };

printf("point(x=%d,y=%d)\n", p1.x, p1.y);
printf("point(x=%d,y=%d)\n", p2.x, p2.y);
printf("point(x=%d,y=%d)\n", p3.x, p3.y);
```

Eftersom struktar har värdesemantik tar följande funktion för att
flytta en punkt i planet in två struktar och skapar en ny, flyttad
punkt, som returneras:

```c
struct point translate(point_t p1, point_t p2)
{
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}
```

Om vi vill skriva om `translate()` så att den punkt som skickas in
förändras (en så-kallad sido-effekt) kan vi göra det med hjälp av
pekare:

```c
void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}
```

Observera att `.`-notationen för att komma åt fält i en strukt
byts ut mot pilar `->` när man gör åtkomst till fält i en **pekare
till en strukt**.

En anledning till pilnotationen är för att förtydliga att vi inte
vet så mycket om värdet vars fält vi läser och skriver. I den
sista implementationen av `translate()` är det t.ex. möjligt att
anropa translate med samma argument två gånger:

```c
point_t p = { .x = 10, .y = 7 };
translate(&p, &p);
```

(observera `&p` eftersom funktionen vill ha adressen till där
punkten finns, inte en kopia av själva punkten).

Om translate anropas med samma punkt som första och andra argument
kommer även det andra argumentet att förändras. Det är förmodligen
lite överraskande (varför skulle den det?) och detta illustrerar
att pekare är kraftfulla men också knepiga att programmera med.


## Punkter, rektanglar och cirklar

Börja med att skapa en ny fil `geo.c` med en tom `main()`-metod etc.
Kopiera dit struktdefinitionen för punkt, samt typaliaset och
den sista `translate()`-funktionen.

1. Skriv en funktion `print_point()` som tar en `point_t *`
   (pekare alltså!) som argument och skriver ut den på terminalen
   på formatet `(x-värde,y-värde)`. Testa den genom att skriva ut
   en lämplig punkt.

2. Skriv funktionen `make_point()` som tar in två heltal som x-
   och y-koordinater och returnerar en `point_t`. Testa den med
   hjälv av `print_point()`.

3. Definiera en strukt för rektanglar. En `struct rectangle`
   representeras som två punkter, dvs. dess övre vänstra hörn och
   dess nedre högra hörn.

4. Definiera ett typalias `rectangle_t` till `struct rectangle`

5. Skriv funktionen `print_rect()` som tar in en pekare till
   en rektangel och skriver ut den på terminalen på formatet
   `rectangle(upper_left=(x,y), lower_right=(x,y))`. Använd
   `print_point()` för att implementera funktionen. Ändra sedan
   `print_point()` till att skriva ut `point(x,y)` istället och
   kompilera om programmet och se att förändringen också får
   genomslagskraft i definitionen av `print_rect()`.

6. Skriv funktionen `make_rect()` som tar in fyra heltal
   och utifrån dem skapar en rektangel. Testa den med hjälp av
   `print_rect()`.

7. Skriv funktionen `area_rect()` som tar in en pekare till en
   rektangel och räknar ut dess area (dvs. basen * höjden).
   Testa den på några enkla exempel vars areor du enkelt kan
   räkna ut själv.

8. Skriv funktionen `intersects_rect()` som tar in två pekare till
   rektanglar och returnerar `true` om det finns minst en punkt i
   planet som finns i båda rektanglarna, annars `false`. Testa den
   med både negativa och positiva exempel, alltså både med
   rektanglar som överlappar och rektanglar som inte gör det.

9. Skriv funktionen `intersection_rect()` som tar in två pekare
   till rektanglar _R1_ och _R2_ och returnerar en ny rektangel
   (med värdesemantik) som är den minsta rektangel som innefattar
   alla punkter som som finns i både _R1_ och _R2_. Testa den
   med de positiva exemplen från föregående fråga.

0. **Frivillig** Definiera en strukt för cirklar med en `point_t`
   som mittpunkt och ett heltal som radie.

0. **Frivillig** Definiera ett typalias `circle_t` för cirklar.

0. **Frivillig** Definiera en `print_circle()` som skriver ut
   `circle(center=point(x,y), radius=r)`.

0. **Frivillig** Definiera en `make_circle()`.

0. **Frivillig** Definiera en `area_circle()` som räknar ut arean
   på en cirkel som `pi * radien^2`. Du kan använda lämpliga
   funktioner och konstanter i `math.h` för att lösa uppgiften.
   Returtypen på `area_circle()` skall vara ett flyttal.


## *Databas (Skall redovisas)

Detta program skall skrivas i filen `db.c`. **Du kommer att kunna återanvända
stora delar av detta program i inlämningsuppgift 1 på kursen!**

En vara har ett namn, en beskrivning, ett pris och en lagerhylla
som avser platsen där den är lagrad.

* Namn och beskrivning skall vara strängar (`char *`)
* Pris skall vara i ören och är därför ett heltal (`int`)
* Lagerhylla skall vara en bokstav åtföljd av en eller flera
  siffror t.ex. A25 men inte A 25* eller 25A (en möjlig datatyp
  för detta är t.ex. `char *` -- det tillåter lagerhyllor som inte
  följer formatet, så kontrollen att endast valida lagerhyllor
  finns i varor måste ske någon annanstans!)


### Deluppgift 1: deklarationer

Deklarera en strukt `item` (för en vara) enligt ovan och ett typalias `item_t`.

### Deluppgift 2: skriva ut varor

Definiera en funktion `print_item` som tar emot en pekare till en vara
och skriver ut en vara på följande format:

    Name:  XXXXX
    Desc:  XXXXX
    Price: XX.XX SEK
    Shelf: XXX   (t.ex. A25)

**Tips:** decimalkommat i `Price` går lätt att göra med
heltalsdivision, modulo och `printf` då vi vet att priset alltid är
i ören. T.ex. `price / 100` blir alltid jämna kronor och `.`:en
kan vara en del av det som skrivs ut.


### Deluppgift 3: skapa en vara

Skriv en funktion `make_item()` som tar som indata namn,
beskrivning, pris och lagerhylla. Funktionen `make_item` kan
förutsätta att lagerhyllans format är korrekt.


### Deluppgift 4: läs in en vara från terminalen

Skriv en funktion `input_item()` som använder hjälpfunktionerna
`ask_question_string()` och `ask_question_int()` för att läsa in namn,
beskrivning och pris på en vara. Definiera ytterligare en
hjälpfunktion `ask_question_shelf()` för att läsa in en lagerhylla
och verfiera att formatet är korrekt enligt specifikationen ovan.

Du kommer att behöva en ny kontrollfunktion för lagerhyllor som är
ganska lik `is_number()` (men första teckenet får vara en
bokstav). Som konverteringsfunktion fungerar `strdup()` eftersom
representationen för lagerhyllan är en sträng.


### Deluppgift 5: kaosmagi

Skriv en funktion `magick()` som genererar ett slumpnamn för
varor med hjälp av kaosmagi. För denna uppgift definieras kaosmagi
som tre slumpmässiga val från tre sträng-arrayer av samma längd som
skickas in till `magick()` och kombineras till ett namn.

Exempel:

    char *array1[] = { "Laser",        "Polka",    "Extra" };
    char *array2[] = { "förnicklad",   "smakande", "ordinär" };
    char *array3[] = { "skruvdragare", "kola",     "uppgift" };

    char *str = magick(array1, array2, array3, 2); // 2 = längden på arrayerna

    puts(str); // Polka-ordinär skruvdragare

Algoritmen fungerar som följer:

1. Skapa en `char buf[255]` att hålla det nya ordet i
2. Välj ett slumpmässigt ord från array1 och skriv in det i `buf`
3. Skriv in ett `'-'` sist i `buf`
4. Välj ett slumpmässigt ord från array2 och skriv in det sist i `buf`
5. Skriv in ett `' '` sist i `buf`
6. Välj ett slumpmässigt ord från array3 och skriv in det sist i `buf`
7. Skriv in ett `'\0'` sist i `buf`
8. returnera `strdup(buf);`

Vi kommer att återkomma till den "magiska" `strdup()`-funktionen
senare i kursen: enkelt förklarat tillhör `buf`-bufferten
`magick()`- funktionen och för att få skicka tillbaka strängen
till den anropande funktionen måste vi duplicera den.

Du kan använda följande `main()`-funktion som läser in ett tal
från kommandoraden, anropar `input_item()` lika många gånger, och
sedan använder `magick()` för att skapa en databas med 16 varor
som sedan skrivs ut på skärmen. Du måste lägga till arrayerna
med ord själv, och deras längd -- sök efter `///` för att hitta
de platser som du måste ändra nedan.

```c
int main(int argc, char *argv[])
{
  char *array1[] = { ... }; /// Lägg till!
  char *array2[] = { ... }; /// Lägg till!
  char *array3[] = { ... }; /// Lägg till!

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0;    // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, ...); /// Lägg till storlek
        char *desc = magick(array1, array2, array3, ...); /// Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     for (int i = 0; i < db_siz; ++i)
     {
       print_item(&db[i]);
     }

  }
  return 0;
}
```

### Lista databasens innehåll

Skriv en funktion `void list_db(item_t *items, int no_items)` som
skriver ut namnen på alla varor i databasen, samt deras index i
arrayen + 1:

    1. XXX
    2. YYY
    ...
    16. ZZZ

Ersätt utskriften av innehållet i databasen med ett anrop till
`list_db()` istället. Använd `db_siz` som storleken på databasen
(`no_items` i `list_db()`).

Observera att databasen är en variabel som är deklarerad i `main()`.


### Editera databasen

Skriv en funktion `edit_db()` som:

1. Frågar efter vilken vara som skall editeras (ett heltal som
   motsvarar heltalen i listningen ovan) med hjälp av `ask_question_int()`
2. Skriver ut varan på skärmen med hjälp av `print_item()`
3. Låter användaren ersätta varan med en annan som läses in med `input_item()`

Fundera över:

1. Vad behöver `edit_db()` ta som inparametrar?
2. Hur sparar vi förändringarna som användaren matar in i databasen?
3. Hur skall programmet bete sig om användaren matar in en siffra
   för vilken det inte finns en vara? (t.ex. -27 eller 42 när
   databasen bara har 16 varor)

**Frivilliga utökningar:**

1. Låt användaren välja vilken del av varan som skall ändras, t.ex. bara priset
2. Bygg in stöd för att lägga in helt nya varor om det finns plats
   (dvs. `db_siz` är mindre än databasens faktiska storlek)
