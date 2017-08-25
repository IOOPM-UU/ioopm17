# Lathund för GitHub
*Baserad på anteckningar av Elsa Rick 2015*

## Clone
* `git clone address` - Addressen hittas vid HTTPS bredvid "Download
ZIP” på GitHub.

## Commit och Push
* `git status` - se vilka filer som har ändrats i, vilka som är
  upplagda för commit etc.
* `git add alla-filer-som-ska-commitas` - lägg till filer som ska
  commitas
* `git commit -a -m "meddelande"` - commita alla trackade filer

  Flaggor till `commit`:
  * `-a` - commitar alla filer som någon gång lagts upp för commit
    (med `git add`)
  * `-m "ett meddelande"` - lägger till ett meddelande

* `git push origin branchnamn` - pusha upp dina commits i den
  lokala branchen `branchnamn` till GitHub. Till exempel, `git
  push origin master` för att pusha till `master`.

## Pull - Dra ner filer från GitHub
1. `git checkout origin master` - ställ dig i din lokala master
2. `git pull origin master` - dra ner master från repot online

Om du vill merge:a ändringar i en lokal branch med `master` efter
en pull som ovan:
1. `git checkout origin branchnamn` - ställ dig i branchnamn
2. `git merge origin/master` - merga branchnamn med din lokala master

I bästa fall så merge:ar den automatiskt dina lokala filer med de
neddragna från master. I värsta fall så får du konflikt. Hur man
löser detta manuellt:
1. Kolla vilka filer du får konflikter i (det ska stå när du kör
   pull - "failed merge”)
2. Gå in i de filerna
3. Leta upp konflikter genom att söka upp "HEAD"
4. Lös konflikterna (ta bort koden du inte vill ha, ta bort HEAD
etc, spara)
5. Skapa en merge-commit med `git commit -a -m "merge"`.

## Ångra etc.
* `git reset HEAD filnamn` - ångrar "add"
* `git checkout filnamn` - motsatsen till "add". Om du har ändrat
  i en fil men inte vill spara ändring. **Obs! Om du checkout:ar en
  fil försvinner alla dina ändringar i den filen!**
* `git rm filnamn` - ta bort en fil från ett repo (ändringen
  kommer med i nästa commit)

## Branching
* `git checkout -b branchnamn` - skapa branch
* `git branch` - se alla brancher du har tillgång till
* `git branch -r` - se alla brancher, även de du inte har lokalt
* `git checkout branchnamn` - byt branch till `branchnamn`

*Se till att alltid stå i rätt branch!!!*

### Hämta existerande branch:
1. `git fetch` - Hämta ändringar från GitHub
2. `git checkout branchnamn` - Efter det här står du i branchnamn

## Övrigt
* `git remote -v` - se vilka repon du är kopplad till

## Samarbete med andra

Såhär kommer en vanlig Git-interaktion se ut när du jobbar med
flera andra:
- Du har skrivit klart en kodsnutt i din egen branch och vill att
  andra ska kunna ta del av den
- Du commitar den som vanligt
- Du pushar upp *till din egen branch* och skapar en pull request
  via GitHub-sidan
- Du väntar på att de andra ska se att du har gjort en pull
  request
- Efter att alla har sett och eventuellt diskuterat din ändring,
  så godkänner någon (inte du!) ändringen och mergear

  **OBS! MERGEA INTE DIREKT SJÄLV!** Någon annan än du själv måste
  mergea. Alla måste se vad du har lagt till och godkänna detta.
