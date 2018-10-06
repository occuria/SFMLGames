CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: memo

memo: main.o Card.o GameState.o TextureHolder.o
	g++ $(CFLAGS) -o memo main.o Card.o GameState.o TextureHolder.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

Card.o: Card.cpp Card.h
	g++ $(CFLAGS) -c Card.cpp 

GameState.o: GameState.cpp GameState.h
	g++ $(CFLAGS) -c GameState.cpp

TextureHolder.o: TextureHolder.cpp TextureHolder.hpp
	g++ $(CFLAGS) -c TextureHolder.cpp

clean:
	rm -f memo *.o
