Debuggning
==========

När ditt program avslutas oväntat eller det beter sig
oförutsägbart hittar du felet mycket fortare och effektivare om du
vet **var** felet uppstår och även **varför** felet uppstår. För
detta använder vi programmerare ett debugging- verktyg (svenska:
avlusning). Vi ska använda `gdb` som finns förinstallerat de allra
flesta Linux-distributioner (Ubuntu, Debian, etc.) och finns
tillgängligt till OSX (Sedan OSX 10.9 har `gdb` ersatts av `lldb`.
Gränssnittet är dock mycket likt `gdb`s).

Programmet nedan använder en funktion `plus_ett` som ska öka värdet
i den variabel som skickas in med ett. Kör programmet och
observera att värdet (enligt utskriften) inte ökas med ett. Vi ska
nu använda `gdb` för att hitta var felet uppstod i `passbyval.c`
(t.ex. är felet i utskriften eller är det fel i logiken?):

``` c
#include <stdio.h> // för printf

// ökar parametern a med ett som sido-effekt
void plus_ett(int a) {
  a = a + 1;
}

int main() {
  int a = 0;
  for(int i = 0; i < 3; i++) {
    plus_ett(a);
    printf("%d + 1 = %d\n", i, a);
  }
  return 0;
}
```

Se till att programmet i fråga är kompilerat med flaggan `-ggdb`
och starta `gdb` genom att köra kommandot `gdb passbyval`
(förutsatt att `passbyval` är namnet du gav till det kompilerade
programmet).

Funktionen `plus_ett` är huvudmisstänkt. Vi ber `gdb`
pausa programmet vid rad 11 och 12 så vi kan titta på värdet i
variabeln `a` före och efter funktionsanropet. Ställ in
pauserna (breakpoints) genom att skriva:

```
    (gdb) break 11
    (gdb) break 12
    (gdb) run
```

Notera att "`(gdb)`" är prompten, och inget du ska skriva själv.
Efter run så kör `gdb` programmet och stannar vid rad 11.
Undersök värdet på variablen a genom att skriva


```
    (gdb) print a
```

Är värdet som det ska? Be `gdb` fortsätta:

```
    (gdb) continue
```

Undersök värdet igen och konstatera att funktionen inte gör vad
den var tänkt att göra. Rensa pauserna och be `gdb` att
stanna i funktionen:

```
    (gdb) delete
```

Tryck "y" för yes om `gdb` frågar om du verkligen vill ta bort alla pauser.

```
    (gdb) break plus_ett
    (gdb) run
```

Om `gdb` frågar om den ska starta om från början så svara "y" för yes.
När programmet stannar kan du själv undersöka vad som händer på varje rad
genom att stega igenom funktionen:

```
    (gdb) step
    (gdb) step
    (gdb) step
    ...
```

För att fortsätta köra programmet till nästa paus (eller tills
programmet avslutas) används kommandot `continue`. Givetvis
behöver vi inte vara så noga att stava rätt till "continue" och
"step" varje gång utan `gdb` tillåter kortkommandot "c" för
continue och "s" för "step". För att avsluta `gdb` skriver du
"quit" eller "q".

Koden tycks onekligen lite ogenomtänkt eftersom funktionen inte
förändrar värdet på variabeln `a` som är deklarerad i
main-funktionen, utan bara sin egen lokala kopia (kom ihåg att
värden kopieras till argumentet i funktionen vid funktionsanrop).

Ett sätt att få koden att göra rätt är att skicka *adressen* till
`a` som argument istället, och göra så att `plus_ett` ändrar på
värdet som ligger på den här adressen. Ändra rad 11 till
`plus_ett(&a)`, och sätt en asterisk (`*`) framför alla
förekomster av `a` i funktionen `plus_ett` (Oroa dig inte om du
inte förstår hur det här fungerar än. Det kommer att förklaras
senare i kursen!). Kompilera programmet och kör igen!

Ett annat sätt att utröna var problem uppstår är att låta `gdb`
skriva ut vilka funktioner som programmet hoppade igenom för att
ta sig till raden där problemet uppenbarar sig. En sådan sekvens
av funktionsanrop kallas för ett *backtrace*. `gdb` visar den här
sekvensen om debuggningen stannar någonstans och vi ger `gdb`
kommandot `backtrace` eller `bt`. Nedan har programmet stannats
efter anropet till `plus_ett`. Kommandot `bt` ger då

```
(gdb) bt
#0  plus_ett (a=0) at passbyval.c:5
#1  0x0000000000400534 in main () at passbyval.c:11
(gdb)
```

vilket ska tolkas som att exekveringen av programmet gick från
`main` (indikeras med ett s.k. frame-nummer: `#1`) till
`plus_ett` (frame-nummer `#0`).

Om man har ett program som kraschar och kör det utan breakpoints i
`gdb` så kommer programmet att pausa precis i ögonblicket där
kraschen sker, så att man kan se vilken rad kraschen skedde på,
vilka funktioner som hade anropats och vilka värden alla variabler
hade. Ovärderlig information när man ska lista ut vad som är fel!

### Att ta med sig:
* Debuggern är din vän
* Kompilera alltid med debugflaggorna påslagna när du
  utvecklar
* Att bara köra ett kraschande program i `gdb` för att se
  utskriften är ofta nog för att lösa felet
