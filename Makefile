DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./build
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, ${notdir ${SRC}})

TARGET = zcc

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -Wall -std=c++11 -I ${DIR_INC}
MD = mkdir
MFLAGS = -p

all:${DIR_OBJ} ${BIN_TARGET}

${BIN_TARGET}:${OBJ}
	$(CC) $(CFLAGS) -o $@ $^

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

${DIR_OBJ}:
	$(MD) $(MFLAGS) $(DIR_BIN)
	$(MD) $(MFLAGS) $(DIR_OBJ)

.PHNY:clean

clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
