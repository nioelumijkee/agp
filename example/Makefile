.PHONY: all clean

PROGNAME = example
SOURCES = example.c ../src/agp.c
INCLUDEDIR = "../src"

CC = gcc
CFLAGS = -Wall -W -pedantic -Wall -Wno-deprecated-declarations -Wno-pointer-arith
CFLAGS += -I$(INCLUDEDIR)
LIBS =

all: $(PROGNAME)

$(PROGNAME): $(SOURCES:.c=.o)
	$(CC) -o $(PROGNAME) $(SOURCES:.c=.o) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o "$*.o" -c "$*.c"

clean:
	rm -f *.o
	rm -f $(INCLUDEDIR)/*.o
	rm -f $(PROGNAME)
