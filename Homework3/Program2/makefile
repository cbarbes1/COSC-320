#Created by Cole Barbes on 09/21/23

PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o IntBinaryTree.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

IntBinaryTree.o : IntBinaryTree.cpp IntBinaryTree.h
	$(CC) $(CPPFLAGS) -c IntBinaryTree.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
