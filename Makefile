VPATH = ./include:./include/tools/grammar/:./tools/grammar/:./src:src/lex \ 
:./src/parser:./src/plugin:./src/plugin/grammar:./src/plugin/table:./src/utils

OBJ_DIR = build
# complier 
TARGET = bin/zcc
# use it to deal grammar
TOOL = bin/grammar_tool

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o grammar.o parsing_table.o

OBJFS_GRAMMAR = grammar_main.o grammar_tool.o token.o error.o grammar.o parsing_table.o item.o status.o dfa.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

OBJECTS_GRAMMAR = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS_GRAMMAR))

CC = g++

INCLUDE = -Iinclude -Iinclude/tools/grammar

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

# main
$(OBJ_DIR)/main.o: src/main.cpp error.h token.h tokenizer.h
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


# grammar tool
$(OBJ_DIR)/grammar_main.o: tools/grammar/grammar_main.cpp grammar_tool.h error.h item.h grammar.h token.h status.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar_tool.o: tools/grammar/grammar_tool.cpp grammar_tool.h item.h status.h unstd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/dfa.o: tools/grammar/dfa.cpp dfa.h status.h item.h token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/status.o: tools/grammar/status.cpp status.h item.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/item.o: tools/grammar/item.cpp item.h grammar.h token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

# used by tool and main
$(OBJ_DIR)/grammar.o:src/parser/grammar.cpp grammar.h error.h token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing_table.o:src/parser/parsing_table.cpp parsing_table.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc
	-rm -rf bin/grammar_tool
