CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o bintree.o
	g++ -o main main.o bintree.o
main.o:main.cpp bintree.o
	g++ $(CFLAGS) main.cpp
list.o:binnode.h bintree.h bintree.cpp
	g++ $(CFLAGS) bintree.cpp

.PHONY:clean
clean:
	-rm -rf *.o