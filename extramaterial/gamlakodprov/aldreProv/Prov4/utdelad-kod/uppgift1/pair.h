/* Skapar ett nytt par och returnerar en pekare till det */
Pair mkPair(T fst, T snd)

/* Uppdaterar first-fältet i pair att peka på fst */
void sfst(Pair pair, T fst)

/* Uppdaterar second-fältet i pair att peka på snd */
void ssnd(Pair pair, T snd)

/* Returnerar innehållet i first-fältet för ett par */
... fst(...)

/* Returnerar innehållet i snd-fältet för ett par */
... snd(...)

/* Jämför två par a och b; returnerar 1 om a:s och b:s first-fält
pekar på samma data, och a:s och b:s second-fält också pekar på
samma data, annars 0 */ 
... pcmp(...)
