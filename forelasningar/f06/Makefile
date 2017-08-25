# Här kan vi definiera variabler. Vi "läser" en variabel med
# syntaxen $(CC).
CC=clang
FLAGS=-std=c11 -Wall -Werror

# Om ingen regel i makefilen anges körs den första regeln. Den ges
# ofta namnet "all", och bör bygga allt (för någon bra definition
# av "allt").
all: greeter tester

# Här är en *rule* (regel) vars *target* (mål) är greeter, och
# vars *dependencies* (beroenden) är greeter.c, util.o och
# peron.o. Kommandot "make greeter" försöker skapa filen "greeter"
# med hjälp av denna regel. Om någon fil inte finns kommer make
# försöka skapa den med hjälp av sina andra regler.
greeter: greeter.c util.o person.o
	$(CC) $(FLAGS) greeter.c util.o person.o -o greeter

util.o: util.c util.h
	$(CC) $(FLAGS) util.c -c

person.o: person.c person.h
	$(CC) $(FLAGS) person.c -c

tester: tester.c person.o util.o
	$(CC) $(FLAGS) tester.c person.o util.o -o tester

# Ett @ framför en rad gör att make inte skriver ut vilket
# kommando den kör. I den här regeln gör det att "make test"
# skriver ut
#
#    Running tests...
#    Test successful!
#
# istället för
#
#    echo "Running tests..."
#    Running tests...
#    ./tester < test_in.txt
#    Test successful!
test: tester
	@echo "Running tests..."
	@./tester < test_in.txt

# make clean är en annan vanlig regel som städar bort alla filer
# som makefilen kan bygga. Notera -f som gör att rm inte klagar om
# filen inte finns.
clean:
	rm -f greeter
	rm -f tester
	rm -f *.o

###################
# Överkurs i Make #
###################

# $^ är en speciell variabel som betyder "alla dependencies för
# den här regeln". Nedan ersätts $^ med "tester.c asker.o".
# $@ är en speciell variabel som betyder "målet för den nuvarande
# regeln". Nedan ersätts $@ med "tester". Notera att regeln gör
# samma sak om vi skriver den som ovan, alltså utan
# specialvariabler!
# tester: tester.c person.o util.o
# 	$(CC) $(FLAGS) $^ -o $@

# $< är en speciell variabel som betyder "den första dependencyn
# för den här regeln. Nedan ersätts $< med "person.c". Jämför med
# $^, som inkluderar alla dependencies! Följande regel är
# ekvivalent med regeln för person.o
# person.o: person.c person.h
# 	$(CC) $(FLAGS) $< -c

# Båda reglerna för util.o och person.o skulle kunna ersättas med
# nedanstående regel som säger ungefär "för att bygga foo.o är vi
# beroende av foo.c och foo.h" (där foo kan bytas ut mot vilket
# namn som helst).
# %.o: %.c %.h
# 	$(CC) $(FLAGS) $< -c