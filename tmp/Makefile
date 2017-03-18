TARGET = zcc

INC = -I./include -I./src/lex -I./src/parser -I./src/plugin -I./src/utils

DIR_OBJ = build

DIR_TEST = test

DIR_SRC = src

DIR_SRC_LEX = src/lex

DIR_SRC_PARSER = src/parser

DIR_SRC_UTILS = src/utils

DIR_SRC_PLUGIN = src/plugin

BIN_TARGET = ${DIR_TEST}/${TARGET}

SRC = $(wildcard ${DIR_SRC}/*.cpp ${DIR_SRC_LEX}/*.cpp ${DIR_SRC_UTILS}/*.cpp ${DIR_SRC_PARSER}/*.cpp ${DIR_SRC_PLUGIN}/*.cpp)

OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, ${notdir ${SRC}})

CC = g++

CPPFLAGS = -Wall -std=c++11 ${INC}

all:prepare ${BIN_TARGET}

${BIN_TARGET}:${OBJ}
	$(CC) $(CPPFLAGS) -o $@ $^

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	@echo $< $@
	$(CC) $(CPPFLAGS) -c $< -o $@

prepare:
	@echo $(SRC)
	@echo $(OBJ)
	mkdir -p test
	mkdir -p build


.PHNY:clean

clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
