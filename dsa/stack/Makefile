CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o stack.o
	g++ -o main main.o stack.o
main.o:main.cpp stack.o
	g++ $(CFLAGS) main.cpp
stack.o: stack.cpp stack.h
	g++ $(CFLAGS) stack.cpp
.PHONY:clean
clean:
	-rm -rf *.o