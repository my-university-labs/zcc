OBJ_DIR = build
# complier
TARGET = bin/zcc
# use it to deal grammar
TOOL = bin/parsingtable_creater

OBJFS = main.o tokenizer.o token.o parser.o symboltable.o error.o grammar.o parsing_table.o translate.o

OBJFS_GRAMMAR = pmain.o grammar_tool.o token.o error.o grammar.o parsing_table.o status.o dfa.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

OBJECTS_GRAMMAR = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS_GRAMMAR))

CC = g++

INCLUDE = -Iinclude -Iinclude/lex -Iinclude/parser -Iinclude/plugin -Iinclude/utils -Iinclude/tools/grammar -Iinclude/translate

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
$(OBJ_DIR)/main.o: src/main.cpp include/utils/error.h include/parser/parser.h include/translate/translate.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/tokenizer.o:src/lex/tokenizer.cpp include/lex/tokenizer.h include/plugin/symboltable.h include/plugin/token.h include/utils/error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/token.o:src/plugin/token.cpp include/plugin/token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o:src/parser/parser.cpp include/parser/parser.h include/plugin/token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltable.o:src/plugin/symboltable.cpp include/plugin/symboltable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp include/utils/error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/translate.o:src/translate/translate.cpp include/translate/translate.h include/plugin/token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

# grammar tool
$(OBJ_DIR)/pmain.o: src/tools/parsingtable_creater/pmain.cpp include/tools/grammar/grammar_tool.h include/utils/error.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar_tool.o: src/tools/parsingtable_creater/grammar_tool.cpp include/tools/grammar/grammar_tool.h include/tools/grammar/dfa.h include/utils/error.h include/plugin/grammar.h include/tools/grammar/item.h include/plugin/parsing_table.h include/tools/grammar/status.h include/plugin/token.h include/unstd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/dfa.o: src/tools/parsingtable_creater/dfa.cpp include/tools/grammar/dfa.h include/tools/grammar/status.h include/tools/grammar/item.h include/plugin/token.h include/unstd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/status.o: src/tools/parsingtable_creater/status.cpp include/tools/grammar/status.h include/tools/grammar/item.h
	$(CC) $(CPPFLAGS) -c $< -o $@

# used by tool and main
$(OBJ_DIR)/grammar.o:src/plugin/grammar.cpp include/plugin/grammar.h include/utils/error.h include/plugin/token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing_table.o:src/plugin/parsing_table.cpp include/plugin/parsing_table.h include/tools/grammar/status.h include/plugin/token.h
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc
	-rm -rf bin/parsingtable_creater

.PHONY: windows-clean

windows-clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc.exe
	-rm -rf bin/parsingtable_creater.exe