VPATH = ./include:./src:src/lex:./src/parser:./src/plugin:./src/plugin/grammar:./src/plugin/table:./src/utils

OBJ_DIR = build

TARGET = test/zcc

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o grammar_dealer.o element.o grammar.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

CC = g++

INCLUDE = -Iinclude -Isrc/lex/ -Isrc/parser -Isrc/plugin -Isrc/plugin/grammar -Isrc/plugin/table -Isrc/utils

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

$(OBJ_DIR)/symboltable.o:src/plugin/table/symboltable.cpp symboltable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar_dealer.o:src/plugin/grammar/grammar_dealer.cpp grammar_dealer.h element.h grammar.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/element.o:src/plugin/grammar/element.cpp element.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar.o:src/plugin/grammar/grammar.cpp grammar.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -rf build/*.o
	-rm -rf test/zcc
