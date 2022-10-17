.PHONY: all clean

CC = gcc
CFLAGS = -Wall -W -pedantic -Wall -Wno-deprecated-declarations -Wno-pointer-arith
CFLAGS += -I..
LIBS =
PROGNAME = out

SOURCES = main.c ../argparse.c

all: $(PROGNAME)

$(PROGNAME): $(SOURCES:.c=.o)
	$(CC) -o $(PROGNAME) $(SOURCES:.c=.o) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o "$*.o" -c "$*.c"

clean:
	rm -f *.o
	rm $(PROGNAME)
