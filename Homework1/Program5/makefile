# This file was created by: Cole Barbes on 09/04/23

PROG = prog5
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make

