# Variabler för att lätt kunna ändra på många regler samtidigt
CC=gcc
FLAGS=-Wall -ggdb -std=c11

# Den första regeln är den som körs om inget mål anges
all: calc test

# calc är beroende av calc.c och stack.o
calc: calc.c stack.o
	$(CC) $(FLAGS) -o calc calc.c stack.o

# $@ = målets namn, $< = det första beroendets namn (jmfr med calc ovan)
test: test.c stack.o
	$(CC) $(FLAGS) -o $@ $< stack.o
	./$@

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f test calc stack.o
	rm -rf test.dSYM calc.dSYM # om du kör på Mac
	rm -f *~

# Kör de här målen oavsett tidsstämplar
.PHONY: test clean