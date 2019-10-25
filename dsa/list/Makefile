CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o list.o
	g++ -o main main.o list.o
main.o:main.cpp list.o
	g++ $(CFLAGS) main.cpp
list.o:list.h list.cpp
	g++ $(CFLAGS) list.cpp

.PHONY:clean
clean:
	-rm -rf *.o