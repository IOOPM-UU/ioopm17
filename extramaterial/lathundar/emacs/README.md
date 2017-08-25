Liten Emacs-referens
====================
Elias Castegren, 2013

Det här är en kort genomgång av några väldigt grundläggande
kommandon i Emacs. Dokumentet är inte utförligt eller ens särskilt
pedagogiskt, utan jag har försökt sammanfatta de kommandon som jag
själv har haft mest nytta av (och använder i princip dagligen).
Det är inte en introduktion, utan snarare en resurs för den som
har använt Emacs lite grand och vill lära sig att bli mer
effektiv. Du kan också använda filen `init.el` (se ovan) som
utgångspunkt om du vill konfigurera ditt eget Emacs. Emacs letar
efter inställningar (bland annat) genom sökvägen
`~/.emacs.d/init.el`.

Nästan alla kortkommandon i Emacs innehåller tangenterna Control
och Meta (symbolen som ser ut som en diamant på tangentborden i
datorsalarna). När man skriver ut kortkommandona skriver man `C`
för Control och `M` för Meta. För att till exempel spara en fil
trycker man `C-x C-s`, alltså först "Control x" (håll in Control
och tryck "x"), och sen "Control s" (håll in Control och tryck
"s"). Det är ofta så att "Control bokstav" och "Meta bokstav" gör
liknande saker. `C-f` flyttar till exempel fram markören ett
tecken, medan `M-f` flyttar fram den ett helt ord. På datorer som
inte har en Meta-tangent brukar man kunna använda ESC eller Alt
istället. På Mac-datorer funkar Cmd eller Alt (beroende på vilken
version av Emacs man kör). I det här dokumentet skrivs
specialtangenter som space, delete och return ut med vinkelhakar:
`<space>`, `<del>` och `<ret>`

Det bästa sättet att lära sig är att helt enkelt försöka använda
alla kommandon så ofta som möjligt. Varje gång man gör något, om
det så är kopiera text eller bara flytta markören, så ska man
fundera på hur man kan göra det med så få knapptryckningar som
möjligt. I början kommer det kännas omständligt att leta upp
kortkommandon för allt man ska göra, men efter ett tag sätter det
sig i fingrarna och då kommer man att bli mer effektiv i sitt
arbete. Sist i dokumentet finns en sida som sammanfattar några
användbara kommandon. Den kan man med fördel skriva ut och låta
ligga bredvid datorn när man arbetar. Här följer en kort
beskrivning av dessa kommandon.

## Öppna filer och hantera buffrar

När man startar Emacs är det första man vill göra att välja vilken
fil man vill jobba med. För att öppna en fil är kommandot `C-x
C-f` (`f` som i *find file*). Om filen inte finns kommer den att
skapas. Sparar gör man med `C-x C-s` (*save file*), eller `C-x
C-w` (*write file*) om man vill ange ett nytt namn på filen. Rent
tekniskt skapas en ny fil när man sparar för första gången.

När man öppnar en fil i Emacs läses den in till en buffer. Man kan
ha flera buffrar inlästa samtidigt, och man byter buffer genom att
trycka `C-x b` och ange namnet på buffern man vill byta till. `C-x
C-b` visar en lista på alla inlästa buffrar, och `C-x k` (*kill
buffer*) stänger den aktiva buffern.

Om man vill kunna se flera buffrar samtidigt kan man dela
Emacs-fönstret horisontellt (`C-x 2`) eller vertikalt (`C-x 3`).
Man byter mellan öppna fönster med `C-x o` (*other window*) eller
genom att klicka i ett fönster. `C-x 0` stänger det aktiva
fönstret, och `C-x 1` stänger alla fönster förutom det aktiva.


## Navigering

Man scrollar ner i ett fönster med `C-v` (*view next screen*) och
upp med `M-v`. `C-l` (*center **l**ine*) centrerar fönstret vid
markören. Trycker man `C-l` flera gånger så scrollas fönstret så
att markören hamnar överst eller underst i fönstret.

Kortkommandona för att flytta markören är `C-f` (*forward*), `C-b`
(*backward*), `C-n` (*next line*) och `C-p` (*previous line*).
Håller man in meta-tangenten istället för control (alltså `M-f`
och `M-b`) flyttar man markören hela ord istället. Det finns också
kortkommandon för att (bland annat) flytta markören till början
eller slutet av den nuvarande raden, meningen, funktionen eller
buffern.

Man kan flytta markören med piltangenterna (i kombination med
control- och meta-tangenterna) eller genom att klicka med musen
också, men med kortkommandona går det betydligt snabbare och man
slipper flytta händerna.

Varje gång man gör något "särskilt" i Emacs (markerar text,
klipper ut eller kopierar något, söker, och så vidare) så sparas
markörens nuvarande position högst upp i den så kallade
mark-stacken. För att hoppa till den position som är överst i
mark-stacken använder man `C-u C-<space>`. Det tar också bort den
positionen från mark-stacken. Ett bra sätt att snabbt komma
tillbaka till "där man nyss var" är att trycka `C-u C-<space>`
några gånger.


## Redigera text

Om man vill ta bort text i Emacs kan man ta bort enskilda tecken
bakåt med `<del>` (backspace) och framåt med `C-d` (*delete*). När
man tar bort mer text åt gången så klipper man egentligen ut den
(så att man kan klistra in den igen). Man kan ta bort hela ord
bakåt och framåt med `M-<del>` och `M-d`. Med `C-k` (*kill line*)
tar man bort resten av raden från och med markören. `C-0 k` tar
bort raden fram till markören

Trycker man `C-<space>` så börjar man markera text från markörens
nuvarande position tills man gör något med markeringen (eller
avbryter med `C-g`). Om man vill utvidga markeringen åt andra
hållet kan man trycka `C-x C-x` (*exchange point and mark*) för
att flytta markören till där man började markeringen (utan att
förlora det man redan har markerat). Man kan också (bland annat)
markera ett helt stycke, en hel funktion eller hela buffern.

När man har markerat text klipper man ut den med `C-w` (*wipe*)
eller kopierar med `M-w`. Klistra in gör man sen med `C-y`
(klistra in kallas *yank* i Emacs). För att komma åt gamla saker
man har klippt ut kan man trycka `M-y` efter att man tryckt `C-y`.
Då bläddrar man igenom allt man har klippt ut hittills.


## Söka och ersätta

Ett annat snabbt sätt att navigera i en fil är att söka efter
textsträngar. Trycker man `C-s` (*search*) eller `C-r` (*reverse
search*) kommer Emacs börja leta efter inmatad text framåt eller
bakåt i filen. Trycker man `C-s` eller `C-r` igen så letar den
efter nästa förekomst i filen.

Om man vill ersätta alla eller vissa förekomster av en textsträng
kan man använda kommandot `M-%` (`M-Shift-5` på vanliga svenska
tangentbord). Man får då mata in texten man söker efter och vad
man vill ersätta den med. För varje förekomst av söksträngen får
man sen ange med `y` (*yes*) och `n` (*no*) om man vill att den
ska bytas ut eller inte (trycker man `?` får man se fler möjliga
svarsalternativ). För att byta ut alla förekomster kan man använda
kommandot `M-x replace-string` istället.


## Terminal i Emacs

Man kan köra enskilda terminalkommandon från Emacs genom att
trycka `M-!` (`M-Shift-1`) och ange ett kommando. Anger man till
exempel `ls` får man se alla filer som finns i samma katalog som
den aktiva filen. Det går också att öppna en terminal i ett
Emacs-fönster med kommandot `M-x shell`. Den fungerar precis som
ett vanligt terminalfönster, med skillnaden att man måste hålla in
control för att bläddra mellan tidigare inmatningar med hjälp av
piltangenterna.

## Ångra och avbryt

Om man vill ångra tidigare ändringar använder man antingen `C-x u`
(*undo*) eller `C-_ `. Om man råkar påbörja ett oönskat kommando
kan man avbryta det med `C-g`. Slutligen kan man spara alla
inlästa buffrar och avsluta Emacs med `C-x C-c`.


# Och sen då?

När man har lärt sig vad som står i det här dokumentet kan man
börja leta vidare efter mer utförliga källor. Ett ställe att börja
kan till exempel vara lektionen man får om man trycker `C-h t` i
Emacs. Referensbladet i `cheatsheet.pdf` ovan är baserat på ett
större referensblad men medvetet förkortat och förenklat för att
vara överskådligt. När man känner sig säker på det grundläggande
så kan ett bra nästa steg vara att skaffa ett större referensblad,
till exempel något av de många man hittar när man googlar "emacs
cheat sheet". Man kan förstås också installera Emacs på sin
hemdator.

En favoritfunktionalitet som det här dokumentet inte har tagit upp
är inspelning och uppspelning av macron. Trycker man `C-x (` så
börjar man spela in alla tangenttryckningar man gör, tills man
avslutar med `C-x )`. Man kan sen spela upp sin senaste inspelning
med `C-x e`, som står för *execute macro*. Det är användbart om
man vill upprepa någonting flera gånger. Som ett enkelt exempel
kommer här ett macro som skriver en `printf`-sats med radbrytning
och flyttar markören till argumentsträngens början:

```
C-x ( printf("\n");  M-b C-b C-x )
```

Efter att ha spelat in ovanstående macro kan man alltså trycka
`C-x e` för att få en `printf`-sats med markören på rätt ställe.
Det går också att upprepa vilket kommando som helst ett visst
antal gånger genom att trycka `C-u 5` (för något värde på 5) och
sen vilket kommando man vill upprepa. Vill man ta bort fyra på
varandra följande rader kan man alltså trycka `C-u 4 C-k`. Prova
också att skriva

```
C-x ( Emacs är bäst <ret> C-x ) C-u 100 C-x e
```

På frågan "Kan man göra det här i Emacs" är svaret nästan alltid
"Ja", framförallt om det handlar om effektiv textredigering. Det
går också att använda Emacs till exempel som webbläsare,
e-postklient, chattklient, PDF-läsare, filhanterare, kalkylator,
kalender och att-göra-lista. Hur insnöad man vill bli är upp till
var och en (jag tycker till exempel inte att det är något fel på
Chrome eller Firefox som webbläsare).

Lycka till i ditt framtida liv som Emacs-fantast!
