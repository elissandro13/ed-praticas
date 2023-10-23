CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/heap.o $(OBJ)/main.o $(OBJ)/unionFind.o
HDRS = $(INC)/heap.hpp $(INC)/unionFind.hpp
CFLAGS = -Wall -c -g -I$(INC)

EXE = $(BIN)/main

 
.PHONY: all debug clean 

all: $(BIN)/pa8.out

debug: $(BIN)/pa8.out
	

#colocar -pg para debugar


$(BIN)/pa8.out: $(OBJS)
	$(CC)  -o $(BIN)/pa8.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/unionFind.o: $(HDRS) $(SRC)/unionFind.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/unionFind.o $(SRC)/unionFind.cpp

$(OBJ)/heap.o: $(HDRS) $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/heap.o $(SRC)/heap.cpp


	
clean:
	rm -f $(BIN)/*.out $(EXE) $(OBJS) gmon.out
