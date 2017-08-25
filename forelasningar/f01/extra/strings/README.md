Strängar och tecken
===================

## Tecken

I C är en variabel som deklarerats med typen `char` inget annat än
ett (något förklätt) heltal (jämför med `Char` i till exempel
Haskell, som är en helt egen datatyp). Teckenkonstanter som `'a'`
och `'?'` är **precis samma sak** som motsvarande ASCII-värde (97
respektive 63). Att skriva `'a' + 3` är alltså helt okej i C, och
det kommer ge precis samma resultat som om man skrev `97 + 3`.

### `printf`

Hittills har vi använt `printf` utan att reflektera så mycket över
hur den funktionen fungerar. Det ska vi råda bot på nu!

`printf` är en funktion som används för att skriva ut formaterad
text (f:et i slutet av namnet står för "format"). Funktionen tar en
så kallad formatsträng och ett godtyckligt antal andra värden som
argument. Formatsträngen är en vanlig sträng som kan innehålla ett
antal tecken med speciell betydelse. Så kallade "escape-characters"
inleds med backslash och används för att skriva ut speciella tecken,
till exempel `\n` för radbrytning eller
`\t` för tab. Anropet

``` c
printf("Hej!\nHopp\tHejsan!\n");
```

skriver ut "Hej!" och "Hopp Hejsan" på varsin rad, med en tab
mellan "Hopp" och "Hejsan".

Formatsträngen kan också innehålla "formatspecifikationer", som
inleds med ett procenttecken (`%`). Formatspecifikationer anger hur de
andra argumenten till `printf` ska skrivas ut. Den första
formatspecifikationen i strängen anger formatet för det första
argumentet efter formatsträngen, den andra för den andra, och så
vidare. Exempel på formatspecifikationer är

* `%d` -- Ett heltal
* `%f` -- Ett flyttal
* `%c` -- Motsvarande ASCII-tecken
* `%s` -- En sträng

Om vi antar att `name` är en sträng och `age` ett heltal så
skriver följande anrop ut båda dessa värden:

``` c
printf("Jag heter %s och är %d år gammal", name, age);
```

Som en kort övning på att använda printf ska vi nu skriva ett program
som skriver ut hela ASCII-tabellen:

1. Öppna en ny fil och döp den till `ascii.c`.

2. Skriv det gamla vanliga main-skelettet och inkludera `stdio.h`.
  Skriv en `for`-loop där loop-variabeln går från 0 till och
  med 127. Inuti loop-kroppen ska du skriva ett anrop till
  `printf` som skriver ut loop-variabelns värde både som heltal
  och som ASCII-tecken. När du är klar borde resultatet se ut
  ungefär så här:

  ``` c
    #include <stdio.h>

    int main(){
      for (int i = 0; i < 128; ++i){
        printf("%d\t%c\n", i, i);
      }
      return 0;
    }
  ```

3. Notera att `i` förekommer som argument till funktionen två
  gånger. Den första gången skrivs det ut som ett heltal (genom
  `%d`), och den andra gången som ett tecken (genom `%c`). Prova
  att kompilera och köra och se om utskriften verkar vettig (notera
  att alla ASCII-tecken inte går att skriva ut, till exempel är 10
  ASCII-värdet för radbrytning).

4. Som avslutning kan vi göra tabellen lite snyggare genom att
  sätta dit rubriker. Skriv dit följande rader högst upp i
  main-funktionen:

  ``` c
      printf("ASCII\tChar\n");
      printf("=====\t====\n");
  ```

  Att det sitter en tab (`\t`) mellan kolumnerna ser
  till att det blir ett jämnt avstånd mellan dem.

`printf` erbjuder många fler möjligheter sätt att ange format
(hexadecimal form, tiopotens, antal värdesiffror,
vänsterjustering...). Du kan läsa man-filen för `printf` för att
lära dig mer!

## Strängar

På samma sätt som med tecken så finns det ingen speciell datatyp
för strängar. En sträng representeras helt enkelt som en array av
`char`s, som avslutas med ett `NUL`-tecken (`'\0'`, ASCII-värdet 0).
Strängen `"IOOPM"` är alltså en array bestående av **sex** tecken,
`{'I', 'O', 'O', 'P', 'M', '\0'}`. Denna array är i sin tur är
**precis samma sak** som en array bestående av heltalen `{73, 79,
79, 80, 77, 0}`.

Nu ska vi titta på och ändra i ett program som använder strängar:

1. Öppna filen `cheerleader.c`.

2. Försök lista ut vad programmet gör. Kompilera sedan och kör.

3. På första raden i `main`-funktionen deklareras en array av
  chars som initieras med strängen "Uppsala". Vi hade precis lika
  gärna kunnat skriva ut det som en array:

  ``` c
      char name[] = {'U', 'p', 'p', 's', 'a', 'l', 'a', '\0'};
  ```

  Eftersom tecken i C bara är kortformer för deras ASCII-koder
  hade vi också kunnat skriva

  ``` c
      char name[] = {85, 112, 112, 115, 97, 108, 97, 0};
  ```

  men det torde vara uppenbart att det är mer praktiskt att skriva som
  det redan står i filen (notera att det avslutande `NUL`-tecknet är
  implicit när man skriver en sträng inom citattecken).

4. Loopen i funktionen `cheer` låter loopvariabeln `i` gå från 0
  till (men inte med) det första värde där `name[i]` är `'\0'`.
  Loopen itererar alltså över hela strängen och terminerar när den
  når det avslutande `NUL`-tecknet i `name`.

  Vad händer i loop-kroppen då? Jo, först läses det `i`:te tecknet ut
  i variabeln `letter`, sen skrivs det ut två gånger på varsin rad
  (först som "Ge mig ett ...", sen som ett svar).

  Efter loopen används funktionen `puts` för att skriva ut
  strängen "Vad blir det?", och till sist strängen `name`. Notera
  att `puts` automatiskt lägger till en radbrytning efter
  utskriften (i `printf` var vi tvungna att själva lägga till
  `'\n'`), och att funktionen kan skriva ut en strängvariabel
  direkt.

5. Nu är det dags att utöka programmet! Till att börja med skulle
  vi vilja att det var lite mer umpf i svaren. Om man inkluderar
  `ctype.h` (på samma sätt som `stdio.h` är inkluderad) får
  man tillgång till funktioner som kontrollerar och manipulerar
  `char`s (se man-filen för `ctype`). Till exempel finns
  funktionen `toupper` som gör om en bokstav till motsvarande versal
  ("stora bokstav"). Inkludera `ctype.h` och ändra den sista
  raden i loopen till:

  ``` c
      printf("%c!\n", toupper(letter));
  ```

  Kompilera och kör programmet igen för att kontrollera
  resultatet. Prova gärna att byta strängen i `name`. Prova också
  att använda `tolower` för att göra om `letter` till en gemen
  ("liten bokstav") i den första utskriften.

6. Vi skulle också vilja att den avslutande utskriften var lite
  mer övertygande. Eftersom störst går först så löser vi det på
  samma sätt som sist, genom att skriva ut hela strängen som
  versaler. Det gör vi genom att iterera över strängen och ändra
  varje tecken till motsvarande versal Skriv en sån loop innan den
  sista utskriften i `cheer`! (**OBS** Genom att göra detta
  introducerar vi en bugg! Se nästa avsnitt.)

  När du är klar borde det se ut ungefär så här:

  ``` c
  for (int i = 0; name[i] != '\0'; ++i){
    name[i] = toupper(name[i]);
  }
  ```

### `string.h`

Slutligen ska vi titta på lite av vad man kan göra med de
funktioner som finns i Cs strängbibliotek. För att komma åt dessa
funktioner behöver du inkludera `string.h`. Vi håller oss kvar i
`cheerleader.c` ett litet tag till, och lägger märke till att
funktionen `cheer` permanent ändrar på sitt argument (prova att
skriva `puts(name)` efter funktionsanropet). Bara för att man
ville få sitt namn ropat av en hejaklack är det inte säkert att
man ville få sitt namn permanent ändrat till något annat. Det här
ska vi fixa nu!

1. Vi ska se till att det första `cheer` gör är att kopiera sitt
  argument till en ny sträng. Först låter vi cheer deklarera en ny
  sträng, men för att göra det måste vi veta hur lång den ska vara. Vi
  vill ha en array av `char`s som är lika lång som strängen `name`
  plus ett för `NUL`-tecknet. I `string.h` finns en funktion som
  heter `strlen` som returnerar längden av en sträng (exklusive
  `NUL`-tecknet). Vi inleder `cheer` med följande två rader:

  ``` c
    int len = strlen(name);
    char newName[len + 1];
  ```

2. Härnäst vill vi kopiera innehållet i `name` till `newName`. Det
  gör vi med funktionen `strncpy(s1, s2, n)`, som kopierar
  strängen `s2` till `s1`, dock som mest `n` tecken. Funktionen
  förutsätter att det finns tillräckligt med ledigt minne för att
  utföra kopieringen, men det har vi ju sett till i deklarationen
  av `newName` (funktionen `strcpy` fungerar på samma sätt, fast
  sätter inget maxtak på antalet tecken. Detta gör det svårare att
  garantera att man inte skriver utanför `s1`s gränser!).

  ``` c
      strncpy(newName, name, len);
```

3. Nu är det bara att ändra alla förekomster av `name` i `cheer`
  till `newName` (kom ihåg `M-x query-replace`). När du är klar
  kan du jämföra med `cheerleader_finished.c`. Prova att skriva ut
  `name` efter anropet till `cheer` och se att strängen inte har
  ändrats (Fundera gärna på om man kan skriva funktionen `cheer`
  utan att använda `strncpy`)

Det finns många fler funktioner i strängbiblioteket, till exempel
för att jämföra strängar, slå ihop strängar eller leta efter
förekomster av ett visst tecken. Dubbelkolla alltid vad som finns
i `string.h` (`man string`) innan du skriver en egen
strängfunktion!

## Att ta med sig
* Ett tecken är precis samma sak som ett heltal. Det är hur man
   tolkar värdet som spelar roll
* Strängar är bara arrayer av `char`s. Glöm inte att se till att
   det finns plats för `NUL`-tecknet också! En sträng som är n
   tecken lång tar upp n + 1 `char`s.
* En sträng är **inte** en lista som i Haskell. Tänk alltid på
   strängar som *arrayer*, inget annat.
* Sa vi att en sträng bara är en array?
