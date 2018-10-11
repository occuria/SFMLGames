CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INC=./inc/
SRC=./src/

all: memo

memo: Main.o Card.o Game.o State.o TextureHolder.o BoardDimensions.o EventHandler.o
	g++ $(CFLAGS) -o memo Main.o Card.o Game.o State.o TextureHolder.o BoardDimensions.o EventHandler.o

Main.o: ${SRC}Main.cpp
	g++ $(CFLAGS) -c ${SRC}Main.cpp

Card.o: ${SRC}Card.cpp ${INC}Card.hpp
	g++ $(CFLAGS) -c ${SRC}Card.cpp 

Game.o: ${SRC}Game.cpp ${INC}Game.hpp
	g++ $(CFLAGS) -c ${SRC}Game.cpp 

State.o: ${SRC}State.cpp ${INC}State.hpp
	g++ $(CFLAGS) -c ${SRC}State.cpp

TextureHolder.o: ${SRC}TextureHolder.cpp ${INC}TextureHolder.hpp
	g++ $(CFLAGS) -c ${SRC}TextureHolder.cpp

BoardDimensions.o: ${SRC}BoardDimensions.cpp ${INC}BoardDimensions.hpp
	g++ $(CFLAGS) -c ${SRC}BoardDimensions.cpp

EventHandler.o: ${SRC}EventHandler.cpp ${INC}EventHandler.hpp
	g++ $(CFLAGS) -c ${SRC}EventHandler.cpp

clean:
	rm -f memo *.o
