CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o
	g++ -o main main.o
main.o:main.cpp BST.h
	g++ $(CFLAGS) main.cpp BST.h
.PHONY:clean
clean:
	-rm -rf *.o