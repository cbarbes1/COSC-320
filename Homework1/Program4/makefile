# This file was created by: Cole Barbes on 02/16/23

PROG = prog3
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o Thing.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

Thing.o : Thing.cpp
	$(CC) $(CPPFLAGS) -c Thing.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make