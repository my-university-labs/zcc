OBJECT = main.o grammar.o grammar_dealer.o item.o

CC = g++

CPPFLAGS = -Wall -std=c++11

TARGET = dealer

$(TARGET): $(OBJECT)
	$(CC) $(CPPFLAGS) -c $< -o $@

grammar.o: grammar.cpp grammar.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

grammar_dealer.o:grammar_dealer.cpp grammar_dealer.h
	$(CC) $(CPPFLAGS) -c $< -o $@

item.o: item.cpp item.h

.PHONY: clean

clean:
	rm -rf *.o


