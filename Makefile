CC = gcc
CFLAGS = -O2 -Wall -I ../../../../../include -I .
CFLAGS2 = ../../../../../src/csapp.o -lpthread 

all: morse

morse: morse.c
	$(CC) $(CFLAGS) morse.c $(CFLAGS2)-o morse 

clean:
	rm -f morse *~
