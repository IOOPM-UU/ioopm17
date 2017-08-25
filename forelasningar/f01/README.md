# Föreläsningar under uppstarten (Adams Weckor)

1. [Föreläsning 1](F1.pdf): Grundläggande C-koncept
2. [Föreläsning 2](../f02/F2.pdf): Struktar och pekare
3. [Föreläsning 3](../f03/F3.pdf): Dynamisk minneshantering

![Översikt över innehållet](overview.png)


# Extramaterial 

Nedan finns länkar till ytterligare material om olika ämnen som är
relevanta för oss nu! De täcks till stor utsträckning av
föreläsningarna, men ger ytterligare hjälp och information. Om du
kör fast med en labb kan det vara bra att kolla nedan för hjälp!

* [io](extra/io/) -- grundläggande om I/O
* [arrayer](extra/arrayer) -- grundläggande om arrayer
* [rekursion](extra/rekursion) -- grundläggande om rekursion i C
* [debuggning](extra/debuggning) -- grundläggande om debuggning
* [kompilera](extra/kompilera) -- grundläggande om hur man kompilerar
* [strings](extra/strings) -- grundläggande om strängar



# Utdelad kod föreläsning 1

Se filer i denna katalog. Generellt gäller att `namn.c` var filen
vi började med, medan `namn_fixed.c` är det färdiga resultatet.
`password_getline.c` innehåller en version av `password.c` som
använder `getline` istället för `scanf`. Notera att det kräver
att man manuellt tar bort den medföljande radbrytningen.


# Utdelad kod föreläsning 3

Filen `strdup.c` innehåller definitionen av `strdup()`-funktionen
som redan finns i ditt standardbibliotek.


# Frivilliga övningar du själv kan göra efter labbarna

* Implementera delar av `string.h`. Bra övningar är:
  - `strcat`
  - `strchr`
  - `strncmp`
  - `strncpy`
  - `strncmp`
  - `strspn`
  - `strnstr`

  Kör `man strcat` (etc) för att få en beskrivning av dem.

* Skriv en funktion `rovar` som tar en sträng som input och
  översätter den till rövarspråket. I rövarspråket översätts alla
  vokaler (a, e, i, o, u, å, ä och ö) till sig själva och alla
  konsonanter `c` till `c`o`c`. "Uppsala" översätts alltså tillnn
  "Upoppopsosalola". Fundera på hur lång strängen som rymmer
  rövarspråkssträngen behöver vara i jämförelse med
  ursprungssträngen! (En lämplig skarvning kan vara att ignorera
  svenska vokaler).

* Implementera (enkla versioner av) några av de vanligaste
  terminalkommandona som hanterar text. Se
  [extramaterial-io](extramaterial-io))
  för exempel på hur man skriver/läser till/från fil, eller skarva
  och läs bara från `stdin`.
  - `echo`
  - `cat`
  - `head`
  - `tail`
  - `grep` (för vanlig strängsökning, reguljära uttryck är svårare!)
  - `wc`

  Kör `man echo` (etc) för att få en beskrivning av dem.

* Modifiera rövarspråksprogrammet så att det läser text från
  `stdin`, översätter texten till rövarspråket och skriver den
  till `stdout`.


# En not om svenska tecken 

Det är inte helt enkelt att använda svenska tecken (eller några
andra tecken än vad som behövs för engelska) i de flesta programspråk.
I C kan vi med fördel använda UTF-8-standarden för att skapa
så-kallade multibyte-strängar där specialtecken som å, ä och ö
representeras med fler än ett tecken. Det medför dock t.ex. att
`strlen("åäö")` är 6 och inte 3. Inget stort problem men ibland
något förvirrande.

Flera studenter har märkt att teckenliteralen `'å'` inte är väldefinierad,
eftersom å inte ryms i en byte. En teckenliteral som använder >1 byte
kan skrivas med `L'å'`, men det går inte t.ex. att jämföra enkelt mellan
`'a'` och `L'a'`.

Biblioteken `wctype.h` och `wchar.h` går med fördel att använda för
att programmera för rikare teckenuppsättningar. 

[Här](swedish.c) finns ett exempel på ett program som manipulerar
C-strängar med svenska tecken dels via `char *` och `wchar_t *` och
`string.h` och `wchar.h`. Du kan med fördel använda kod från detta
program för att konvertera en C-sträng till `wchar_t *` om du skulle
t.ex. vilja göra en koll `str[i] == L'å'` (observera L:et i literalen).
