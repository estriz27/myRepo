CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = ishell

all: $(EXECS)

doc:
	doxygen

$(OBJ)/wrappers.o: $(SRC)/wrappers.c $(SRC)/wrappers.h
	$(CC) $(CFLAGS) -c $(SRC)/wrappers.c -o $(OBJ)/wrappers.o

ishell: $(SRC)/ishell.c $(OBJ)/wrappers.o 
	$(CC) $(CFLAGS) $(SRC)/ishell.c $(OBJ)/wrappers.o -o $(BIN)/ishell -lreadline

clean:
	/bin/rm -f *.o *~ core $(ALL)
