# created by cole barbes
PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o tinyfiledialogs.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp RBTree.h Map.h
	$(CC) $(CPPFLAGS) -c main.cpp

tinyfiledialogs.o : tinyfiledialogs.cpp
	$(CC) $(CPPFLAGS) -c tinyfiledialogs.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
