CC=gcc
FLAGS=-Wall -std=c11 -ggdb

all: fact calc db list

fact: fact.c
	$(CC) $(FLAGS) fact.c -o fact

calc: calc.c
	$(CC) $(FLAGS) calc.c -o calc

db: db.c
	$(CC) $(FLAGS) db.c -o db

run: db
	./db my_database.db

clean:
	rm -f calc
	rm -f fact
	rm -f db
	rm -f *.o
	rm -rf *.dSYM
	rm -f *~