VPATH = ./include:./src:src/lex:./src/parser:./src/plugin:./src/utils

OBJ_DIR = build

TARGET = test/zcc

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

CC = g++

INCLUDE = -I./include -I./src/lex/ -I./src/parser

CPPFLAGS = -Wall -std=c++11 $(INCLUDE)

all:$(TARGET)

$(TARGET): prepare $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJECTS)

prepare:
	@-mkdir -p test
	@-mkdir -p build

$(OBJ_DIR)/main.o: src/main.cpp utils.h error.h token.h tokenizer.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/tokenizer.o:src/lex/tokenizer.cpp tokenizer.h symboltable.h token.h error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/token.o:src/lex/token.cpp token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o:src/parser/parser.cpp parser.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltable.o:src/plugin/symboltable.cpp symboltable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: push
push:
	@echo git msg is -> $(msg)
	git add .
	git commit -m $(msg)
	git push origin $(branch)

.PHONY: clean
clean:
	-rm -rf build/*.o
