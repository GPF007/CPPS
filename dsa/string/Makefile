CC=g++
DEBUG=-g
CFLAGS=-c -Wall -std=c++11

main:main.o
	g++ -o main main.o
main.o:main.cc matchs.h karp.h
	g++ $(CFLAGS) main.cc matchs.h karp.h
.PHONY:clean
clean:
	-rm -rf *.o