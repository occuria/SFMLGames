CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system

all: memo

memo: main.o Card.o GameState.o
	g++ $(CFLAGS) -o memo main.o Card.o GameState.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

Card.o: Card.cpp Card.h
	g++ $(CFLAGS) -c Card.cpp 

GameState.o: GameState.cpp GameState.h
	g++ $(CFLAGS) -c GameState.cpp

clean:
	rm -f memo *.o
