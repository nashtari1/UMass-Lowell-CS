CC = g++
CFlags = -Wall -Werror -pedantic -std=c++14 -g -O1
LIBS = -lsfml-system
DEPS = EDistance.h

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

EDistance: EDistance.o main.o
	$(CC) $(CFLAGS) -o EDistance $^ $(LIBS)

all: EDistance

clean:
	rm *.o EDistance
    