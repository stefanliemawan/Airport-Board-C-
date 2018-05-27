CC=g++

CFLAGS=-Wall

all: AirportBoard

AirportBoard: Main.o Flight.o
	$(CC) $(CFLAGS) Main.o Flight.o -o AirportBoard

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp
	
Flight.o: Flight.cpp Flight.h
	$(CC) $(CFLAGS) -c Flight.cpp

clean:
	rm -rf *o AirportBoard
