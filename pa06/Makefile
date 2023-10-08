CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/graph.o $(OBJ)/lista.o $(OBJ)/main.o 
HDRS = $(INC)/graph.hpp $(INC)/ListaAdjacencia.hpp 
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main


all: $(BIN)/main
	

#colocar -pg para debugar

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp   

$(OBJ)/graph.o: $(HDRS) $(SRC)/graph.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/graph.o $(SRC)/graph.cpp  

$(OBJ)/lista.o: $(HDRS) $(SRC)/ListaAdjacencia.cpp
	$(CC) $(CFLAGS) $(SRC)/ListaAdjacencia.cpp -o $(OBJ)/lista.o
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
