CC = gcc
SRC = ./
OBJ = ./
BIN = bin
OBJS = $(OBJ)/main.o
CFLAGS = -Wall -c

EXE = $(BIN)/pa9.out

.PHONY: all clean

run: all
	$(EXE)

all: $(EXE)

$(BIN)/pa9.out: $(OBJS)
	$(CC) -o $(BIN)/pa9.out $(OBJS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c


clean:
	rm -f $(EXE) $(OBJS) gmon.out