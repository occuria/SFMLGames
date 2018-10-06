CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC=./inc/
SRC=./src/

all: memo

memo: Main.o Card.o GameState.o TextureHolder.o
	g++ $(CFLAGS) -o memo Main.o Card.o GameState.o TextureHolder.o

Main.o: ${SRC}Main.cpp
	g++ $(CFLAGS) -c ${SRC}Main.cpp

Card.o: ${SRC}Card.cpp ${INC}Card.h
	g++ $(CFLAGS) -c ${SRC}Card.cpp 

GameState.o: ${SRC}GameState.cpp ${INC}GameState.h
	g++ $(CFLAGS) -c ${SRC}GameState.cpp

TextureHolder.o: ${SRC}TextureHolder.cpp ${INC}TextureHolder.hpp
	g++ $(CFLAGS) -c ${SRC}TextureHolder.cpp

clean:
	rm -f memo *.o
