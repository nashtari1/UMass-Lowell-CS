# CXX = g++
# CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
# LDFLAGS = -lboost_regex -lboost_date_time

# all: ps7

# ps7: ps7.o
# 	$(CXX) $(CXXFLAGS) -o ps7 ps7.o $(LDFLAGS)

# ps7.o: ps7.cpp
# 	$(CXX) $(CXXFLAGS) -c ps7.cpp

# clean:
# 	rm -f ps7 *.o
	
all: ps7

ps7: main.o
	g++ main.o -o ps7 -l boost_regex

main.o: main.cpp
	g++ -c main.cpp -Wall -Werror -pedantic

clean:
	rm *.o ps7
