CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -pedantic -Wextra
LINT = cpplint

PTree: main.o PTree.o
	$(CC) $(CFLAGS) -o PTree main.o PTree.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp PTree.h
	$(CC) $(CFLAGS) -c -o main.o main.cpp

PTree.o: PTree.cpp PTree.h
	$(CC) $(CFLAGS) -c -o PTree.o PTree.cpp

lint:
	$(LINT) main.cpp PTree.cpp PTree.h

all: PTree lint

clean:
	rm -f PTree main.o PTree.o
