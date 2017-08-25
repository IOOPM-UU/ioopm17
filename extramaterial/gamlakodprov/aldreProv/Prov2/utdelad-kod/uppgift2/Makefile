all:	listtest

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -Wall -ggdb -std=c11

list.o: list.c list.h
	$(C_COMPILER) $(C_OPTIONS) -c list.c

driver.o: driver.c
	$(C_COMPILER) $(C_OPTIONS) -c driver.c

lib: list.o

listtest: list.o driver.o
	$(C_COMPILER) $(C_OPTIONS) list.o driver.o -o $@

clean:
	rm -f list.o driver.o listtest
