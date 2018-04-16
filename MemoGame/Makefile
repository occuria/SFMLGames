CFLAGS=-Wall -Werror -lsfml-graphics -lsfml-window -lsfml-system

all: memo

memo: main.o
	g++ $(CFLAGS) -o memo main.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean:
	rm -f memo *.o
