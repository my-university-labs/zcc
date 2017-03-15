SRC = ./src
UTILS = ./src/utils
TARGET = ./bin/zcc

OBJECT = build/LexicalAnalyzer.o build/main.o build/token.o build/zerror.o build/zutils.o

CC = g++
FLAGS = -Wall -std=c++11

all:${TARGET}

${TARGET}:${OBJECT}
	$(CC) $(FLAGS) $(OBJECT)

build/main.o:src/main.cpp include/zerror.h include/LexicalAnalyzer.h
	$(CC) $(FLAGS) -c src/main.cpp 

build/LexicalAnalyzer.o: src/LexicalAnalyzer.cpp include/token.h 
	$(CC) $(FLAGS) -c src/LexicalAnalyzer.cpp

build/token.o:

