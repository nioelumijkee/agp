.PHONY: all clean

CC = gcc
CFLAGS = -Wall -W -pedantic -Wall -Wno-deprecated-declarations -Wno-pointer-arith
LIBS =
PROGNAME = out

all: main.o
	$(CC) -o $(PROGNAME) main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm -f *.o
	rm $(PROGNAME)
