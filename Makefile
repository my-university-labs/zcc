DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, ${notdir ${SRC}})

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -Wall -std=c++11 -I ${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(CFLAGS) -o $@ $^

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHNY:clean

clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
