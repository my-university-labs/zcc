VPATH = ./include:./src:src/lex:./src/parser:./src/plugin:./src/plugin/grammar:./src/plugin/table:./src/utils

OBJ_DIR = build

TARGET = bin/zcc

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

CC = g++

INCLUDE = -Iinclude

CPPFLAGS = -Wall -std=c++11 $(INCLUDE)

all:$(TARGET)

$(TARGET): prepare $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJECTS)

prepare:
	@-mkdir -p bin
	@-mkdir -p build

$(OBJ_DIR)/main.o: src/main.cpp error.h token.h tokenizer.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/tokenizer.o:src/lex/tokenizer.cpp tokenizer.h symboltable.h token.h error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/token.o:src/lex/token.cpp token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o:src/parser/parser.cpp parser.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltable.o:src/plugin/table/symboltable.cpp symboltable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc
