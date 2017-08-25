Iteration vs. rekursion
=======================

En rekursiv definition är rekursiv, det vill säga den refererar
till sig själv. Ett exempel på en rekursiv definition är en
definition av en lista som lyder "en lista är antingen
*tom* eller en *lista* plus ytterligare ett element".
För att en rekursiv definition skall vara sund behövs (minst) ett
*basfall*, som inte refererar tillbaka till den term som
man håller på ett definiera. I vårt exempel säger vi litet
slarvigt att "den tomma listan är en lista". Låt oss beteckna
denna lista `[]`. Nu kan vi använda den *rekursiva* delen
av definitionen för att skapa en ny lista genom att lägga till ett
element till den redan existerande, tomma, listan, t.ex. talet 42.
Då får vi en lista `[42]`. Vi kan upprepa denna procedur och skapa
en lista `[42, 7, 5, 100]` etc. En syntax som bättre fångar
listans rekursiva natur är denna: `(42 (7 (5 (100 ()))))`, där
`()` avser en tom lista. Kan du se varför?


### Definitionen av Fibonaccitalserien

Fibonaccitalserien är ett klassiskt exempel på en rekursiv
definition. Vilket/vilka är basfallet/basfallen? Vilket/vilka är
det/de rekursiva steget/stegen?

> Ett fibonaccital ingår i en sekvens av heltal, där varje tal är summan av de två föregående fibonaccitalen; de två första talen är 0 och 1.
(Citatet taget från Wikipedia)

### Från rekursiv definition till rekursiv implementation

Nedanstående kod som också finns i kursrepot (se `fib-rec.c`)
utgör en funktion skriven i C som räknar fram det n:te talet i
Fibonaccitalserien. Implementationen är rekursiv. Studera hur
koden förhåller sig till definitionen! Vilka delar av koden
motsvarar basfall och vilka delar är rekursiva?

``` c
int fib(int n) {
  if (n == 0) {
    return 0;
  } else {
    if (n == 1) {
      return 1;
    } else {
      return fib(n-1) + fib(n-2);
    }
  }
}
```

Ett enkelt sätt att beskriva en rekursiv implementation är `i`
termer av mönstermatchning mot en rekursiv definition. Om vi
återkopplar till exemplet med definitionen av fibonaccital kan vi
se att vi för varje "probleminstans" `n` först jämför `n` med våra
två basfall (0 och 1) och i de fall de inte matchade går vidare
till det rekursiva steget som kräver att vi räknar ut (eller
känner till) de `n-1`:te och `n-2`:te fibonaccitalen. Notera hur
"problemet hela tiden minskar" -- varje steg i rekursionen minskar
fibonaccitalet som vi försöker räkna ut tills det blir 0 eller 1,
alltså något av basfallen, för vilka svaren är givna från
definitionen ("[...] de två första talen är 0 och 1."). När vi
reducerat problemet till något av basfallen kan vi konstruera ett
svar. Den uträkning som det rekursiva programmet "logiskt utför"
skulle kunna sägas vara denna (för `n=5`):

```
fib(5) = fib(4) + fib(3)
fib(4) = fib(3) + fib(2)
fib(3) = fib(2) + fib(1)
fib(2) = fib(1) + fib(0)
fib(1) = 1 [enligt definitionen]
fib(0) = 0 [enligt definitionen]
fib(2) = 1 + 0 [enligt rad 5 och 6] = 1
fib(3) = 1 + 1 [enligt rad 5 och 7] = 2
fib(4) = 2 + 1 [enligt rad 7 och 8] = 3
fib(5) = 3 + 2 [enligt rad 8 och 9] = 5
```

Vissa rekursiva funktioner kan implementeras med hjälp av
iteration. Iterativa lösningar kan beskrivas som en loop som
upprepar en *imperativ process*. En viktig anledning varför detta
kan vara eftersträvansvärt är att iteration oftast är mer
effektivt (kortare körtid med mindre resurser) än rekursion.
Avancerade kompilatorer försöker ofta översätta rekursiv kod till
iterativ kod dolt för programmeraren av just detta skäl.

Nedan följer en iterativ implementation av funktionen `fib`.
Istället för att reducera problemet till ett basfall och sedan
konstruera ett svar räknar denna implementation fram `n`:te
fibonaccitalet genom att iterativt räkna fram `fib(2)` (med hjälp av
basfallen), sedan `fib(3)` med hjälp av 2:a basfallet och
uträkningen av `fib(2)`, etc.:

```
fib(0) = 0 [enligt definitionen]
fib(1) = 1 [enligt definitionen]
fib(2) = 0 + 1 [enligt rad 1 och 2] = 1
fib(3) = 1 + 1 [enligt rad 2 och 3] = 2
fib(4) = 1 + 2 [enligt rad 3 och 4] = 3
fib(5) = 2 + 3 [enligt rad 4 och 5] = 5
```

Denna uträkning ser trivial ut men implementationen följer inte
samma struktur som den rekursiva definitionen av
fibonaccitalserien och kan anses svårare att läsa:

``` c
int fib(int n) {
  int a = 0;
  int b = 1;
  for (int i=1; i<=n; ++i) {
    int fib_i = a + b;
    a = b;
    b = fib_i;
  }
  return a;
}
```

### Iterativ lösning

På papper, gå igenom vad som händer om man anropar `fib(5)`
ovan. Utför varje rad för sig, ungefär som när du stegade igenom
kod med `gdb` tidigare.

1. Hur förändras värdena på variablerna `a` och `b`?
2. Hur många gånger går programmet igenom loopen på rad 4--8?
3. Variablerna `a` och `b` har dåliga namn --
  finns det bättre namn på dem som skulle göra koden enklare att
  läsa? (Jämför t.ex. med variabeln `fib_i`) som avser det
  `i`:te fibonaccitalet.)

Notera: Du kan kontrollera att du har tänkt rätt genom att stega
igenom programmet med `gdb` och inspektera värdena på variablerna
mellan varje steg.

### Modifierad Iterativ lösning

Öppna `fib-rec.c`. Detta program skriver ut resultatet på följande
format:

```
  foo> ./fib-rec 5
  Fib 5 = 5
  foo>
```

Modifiera programmet så att samtliga beräknade fibonaccital skrivs
ut. När programmet körs skall utskriften se ut så här:

```
  foo> ./fib-rec 5
  Fib 0 = 0
  Fib 1 = 1
  Fib 2 = 1
  Fib 3 = 2
  Fib 4 = 3
  Fib 5 = 5
  foo>
```

Ledning: Satsen som skriver ut text i terminalen heter `printf`.
Du kan använda/flytta den rad som skriver ut det slutgiltiga
resultatet i det ursprungliga programmet. Vi skall experimentera
mer med utskrift senare i detta häfte.

### Hur fungerar retursatsen?

Nedanstående rekursiva funktion är ekvivalent med den första
rekursiva `fib`-funktionen ovan. Studera skillnaderna och förklara
varför funktionerna är lika!

``` c
int fib(int n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib(n-1) + fib(n-2);
}
```
