OBJ_DIR = build
# complier
TARGET = bin/zcc
# use it to deal grammar
TOOL = bin/parsingtable_creater

OBJFS = main.o tokenizer.o token.o parser.o grammar.o parsing_table.o \
    translate.o code.o codemanager.o symboltable.o symboltablemanager.o  error.o

OBJFS_GRAMMAR = pmain.o grammar_tool.o token.o error.o grammar.o \
    parsing_table.o status.o dfa.o

OBJECTS = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS))

OBJECTS_GRAMMAR = $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJFS_GRAMMAR))

CC = g++

INCLUDE = -Iinclude -Iinclude/lex -Iinclude/parser -Iinclude/symboltable \
    -Iinclude/utils -Iinclude/tools/grammar -Iinclude/translate

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

# zcc main
$(OBJ_DIR)/main.o: src/main.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/tokenizer.o:src/lex/tokenizer.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/token.o:src/lex/token.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o:src/parser/parser.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar.o:src/parser/grammar.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing_table.o:src/parser/parsing_table.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/translate.o:src/translate/translate.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/code.o:src/translate/code.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/codemanager.o:src/translate/codemanager.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltable.o:src/symboltable/symboltable.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/symboltablemanager.o:src/symboltable/symboltablemanager.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/error.o:src/utils/error.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# just used by grammar tool
# grammar tool main
$(OBJ_DIR)/pmain.o: tools/parsingtable_creater/pmain.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar_tool.o: tools/parsingtable_creater/grammar_tool.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/dfa.o: tools/parsingtable_creater/dfa.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/status.o: tools/parsingtable_creater/status.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: clean

clean:
	-rm -rf build/*.o
	-rm -rf bin/zcc
	-rm -rf bin/parsingtable_creater

.PHONY: windows-clean

wclean:
	-rm -rf build/*.o
	-rm -rf bin/zcc.exe
	-rm -rf bin/parsingtable_creater.exe