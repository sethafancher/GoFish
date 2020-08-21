CXX = g++

CXXFLAGS = -pedantic --std=c++11 -g

all: test

go_fish.exe: cards.cpp cards_pack.cpp players.cpp go_fish.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump


