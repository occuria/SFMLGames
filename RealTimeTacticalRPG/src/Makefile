CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: tacticalrpg

tacticalrpg: main.o
	g++ $(CFLAGS) -o TacticalRPG main.o && rm *.o

main.o:
	g++ $(CFLAGS) -c ./Main/main.cpp

clean:
	rm -f TacticalRPG *.o
