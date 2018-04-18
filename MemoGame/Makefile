CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system

all: memo

memo: main.o Card.o
	g++ $(CFLAGS) -o memo main.o Card.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

Card.o: Card.cpp Card.h
	g++ $(CFLAGS) -c Card.cpp 

clean:
	rm -f memo *.o
