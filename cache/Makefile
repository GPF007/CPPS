CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main: main.o cache.o
	g++ -o main main.o cache.o
main.o: main.cpp cache.o
	g++ $(CFLAGS) main.cpp
cache.o: cache.cpp cache.h
	g++ $(CFLAGS) cache.cpp
.PHONY:clean
clean:
	-rm -rf *.o