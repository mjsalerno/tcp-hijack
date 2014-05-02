CC = gcc
INCLUDES = -I../include
CFLAGS = -Wall -Werror $(INCLUDES)
LIBS = -lpcap
BIN = tcphijack

.PHONY: clean all run sniff

all: tcphijack sniffer

tcphijack:	tcphijack.o
	$(CC) $(CFLAGS) -o $(BIN) tcphijack.o

sniffer: sniffer.o
	$(CC) $(CFLAGS) -o sniffer sniffer.o $(LIBS)

tcphijack.o: tcphijack.c ../include/tcphijack.h
	$(CC) $(CFLAGS) -c $*.c $(LIBS)

sniffer.o: sniffer.c
	$(CC) $(CFLAGS) -c $*.c $(LIBS)

sniff: sniffer
	sudo ./sniffer

run: tcphijack
	sudo ./$(BIN)

clean:
	rm -f *.o *.out $(BIN) sniffer