# This file was created by: Cole Barbes on 02/16/23

PROG = lab1
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o

$(PROG) : $(OBJS)
        $(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
        $(CC) $(CPPFLAGS) -c main.cpp

Sphere.o : Sphere.h Sphere.cpp
        $(CC) $(CPPFLAGS) -c Sphere.cpp

clean: 
        rm -f core $(PROG) $(OBJS)

rebuild:
        make clean 
        make 

