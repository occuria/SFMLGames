CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: tacticalrpg

tacticalrpg: main.o
	g++ $(CFLAGS) -o tacticalrpg main.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean:
	rm -f tacticalrpg *.o
