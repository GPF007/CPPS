CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o vector.o
	g++ -o main main.o vector.o
main.o:main.cpp vector.o
	g++ $(CFLAGS) main.cpp
vector.o:vector.cpp vector.h
	g++ $(CFLAGS) vector.cpp

.PHONY:clean
clean:
	-rm -rf *.o