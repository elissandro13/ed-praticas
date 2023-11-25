CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/Set.o $(OBJ)/main.o 
HDRS = $(INC)/Set.hpp
CFLAGS = -Wall -c -g -I$(INC)

EXE = $(BIN)/main

 
.PHONY: all debug clean 

all: $(BIN)/pa10.out

debug: $(BIN)/pa10.out
	

#colocar -pg para debugar


$(BIN)/pa10.out: $(OBJS)
	$(CC)  -o $(BIN)/pa10.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/Set.o: $(HDRS) $(SRC)/Set.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Set.o $(SRC)/Set.cpp


	
clean:
	rm -f $(BIN)/*.out $(EXE) $(OBJS) gmon.out
