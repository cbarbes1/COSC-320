PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = ExpressionTree.o Function.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ExpressionTree.o : ExpressionTree.cpp
	$(CC) $(CPPFLAGS) -c ExpressionTree.cpp

Function.o : Function.cpp
	$(CC) $(CPPFLAGS) -c Function.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
