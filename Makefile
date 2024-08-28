CC = gcc
CFLAGS = --std=c2x -Wall -Werror -pedantic
OBJECTS = main.o bit_flags.o
PROGRAM = main
HEADERS = status.h bit_flags.h

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

bit_flags.o: bit_flags.c $(HEADERS)
	$(CC) $(CFLAGS) -c bit_flags.c

clean:
	rm -f $(PROGRAM) *.o *.gch
