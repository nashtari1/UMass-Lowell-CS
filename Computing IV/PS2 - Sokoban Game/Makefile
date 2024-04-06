CC=g++
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c++17

all: Sokoban

Sokoban: main.o Sokoban.o
	$(CC) $(CFLAGS) main.o Sokoban.o -o Sokoban -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Sokoban.o: Sokoban.cpp
	$(CC) $(CFLAGS) -c Sokoban.cpp

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.h

clean:
	rm -f *.o Sokoban