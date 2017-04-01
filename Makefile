VPATH = ./include:./src:src/lex:./src/parser:./src/plugin:./src/plugin/grammar:./src/plugin/table:./src/utils

OBJ_DIR = build

TARGET = bin/zcc

TOOL = bin/grammar_tool

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o grammar.o parsing_table.o item.o

OBJFS_GRAMMAR = grammar_tool.o token.o error.o grammar.o parsing_table.o item.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

OBJECTS_GRAMMAR = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS_GRAMMAR))

CC = g++

INCLUDE = -Iinclude

CPPFLAGS = -Wall -std=c++11 $(INCLUDE)

all:$(TARGET)

tool:$(TOOL)

$(TARGET): prepare $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJECTS)

$(TOOL): prepare $(OBJECTS_GRAMMAR)
	$(CC) $(CPPFLAGS) -o $(TOOL) $(OBJECTS_GRAMMAR)

prepare:
	@-mkdir -p bin
	@-mkdir -p build

$(OBJ_DIR)/main.o: src/main.cpp error.h token.h tokenizer.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar_tool.o: tools/grammar/grammar_tool.cpp grammar_tool.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/tokenizer.o:src/lex/tokenizer.cpp tokenizer.h symboltable.h token.h error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/token.o:src/lex/token.cpp token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o:src/parser/parser.cpp parser.h token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltable.o:src/plugin/table/symboltable.cpp symboltable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar.o:src/parser/grammar.cpp grammar.h error.h token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing_table.o:src/parser/parsing_table.cpp parsing_table.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/item.o: src/parser/item.cpp item.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc
	-rm -rf bin/grammar_tool
