
CC = gcc
HEADERS = -I./

OBJECTS = main.o parser.o calculator.o


main: parser.c $(OBJECTS)
	gcc -o main $(OBJECTS) -lm

parser.c:
	lemon parser.y

.c.o:
	$(CC) -c $(HEADERS) -o $@ $<


.PHONY clean:
	rm -rf *.o parser.c parser.h
	rm main 
	rm *.out