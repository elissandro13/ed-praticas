CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/heap.o $(OBJ)/main.o 
HDRS = $(INC)/heap.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

 
.PHONY: all debug clean 

all: $(BIN)/pa7.out

debug: $(BIN)/pa7.out
	

#colocar -pg para debugar


$(BIN)/pa7.out: $(OBJS)
	$(CC)  -o $(BIN)/pa7.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/heap.o: $(HDRS) $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/heap.o $(SRC)/heap.cpp


	
clean:
	rm -f $(BIN)/*.out $(EXE) $(OBJS) gmon.out
