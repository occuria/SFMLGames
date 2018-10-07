CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC=./inc/
SRC=./src/

all: memo

memo: Main.o Card.o Game.o GameState.o TextureHolder.o BoardDimensions.o
	g++ $(CFLAGS) -o memo Main.o Card.o Game.o GameState.o TextureHolder.o BoardDimensions.o

Main.o: ${SRC}Main.cpp
	g++ $(CFLAGS) -c ${SRC}Main.cpp

Card.o: ${SRC}Card.cpp ${INC}Card.h
	g++ $(CFLAGS) -c ${SRC}Card.cpp 

Game.o: ${SRC}Game.cpp ${INC}Game.hpp
	g++ $(CFLAGS) -c ${SRC}Game.cpp 

GameState.o: ${SRC}GameState.cpp ${INC}GameState.h
	g++ $(CFLAGS) -c ${SRC}GameState.cpp

TextureHolder.o: ${SRC}TextureHolder.cpp ${INC}TextureHolder.hpp
	g++ $(CFLAGS) -c ${SRC}TextureHolder.cpp

BoardDimensions.o: ${SRC}BoardDimensions.cpp ${INC}BoardDimensions.hpp
	g++ $(CFLAGS) -c ${SRC}BoardDimensions.cpp

clean:
	rm -f memo *.o
