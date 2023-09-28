# This file was created by: Cole Barbes on 09/27/23

PROG = prog1
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o crossref.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

crossref.o : crossref.cpp crossref.h
	$(CC) $(CPPFLAGS) -c crossref.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
