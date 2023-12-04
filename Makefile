# needed for csv parser
# g++ -std=c++0x a.o b.o -o prog -lpthread

.PHONY: clean

all: clean build-tm

build-tm:
	g++ -g -Wuninitialized -o ./build/ticketmistress ./src/combined/*.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f ./build/*
