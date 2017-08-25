all:	driver

C_COMPILER   = gcc
C_OPTIONS    = -Wall -ggdb

AUX_EXTENSIONS = "*.o"

stack.o: stack.c
	$(C_COMPILER) -c $(C_OPTIONS) $< -o $@

driver: driver.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@

clean:
	rm -f $(AUX_EXTENSIONS)
