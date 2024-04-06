CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lboost_unit_test_framework

all: TextWriter test

TextWriter: TextWriter.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o TextWriter TextWriter.o RandWriter.o

TextWriter.o: TextWriter.cpp RandWriter.h
	$(CXX) $(CXXFLAGS) -c TextWriter.cpp

RandWriter.o: RandWriter.cpp RandWriter.h
	$(CXX) $(CXXFLAGS) -c RandWriter.cpp

test: test.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o test test.o RandWriter.o $(LDFLAGS)

test.o: test.cpp RandWriter.h
	$(CXX) $(CXXFLAGS) -c test.cpp

lint:
	python cpplint.py TextWriter.cpp RandWriter.cpp RandWriter.h test.cpp

clean:
	rm -f TextWriter test *.o
