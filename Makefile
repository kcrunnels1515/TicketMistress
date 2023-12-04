# needed for csv parser
# g++ -std=c++0x a.o b.o -o prog -lpthread

.PHONY: clean

all: clean build-client build-server

build-client:
	g++ -Wuninitialized -o ./build/client ./src/client/*.cpp -lsfml-graphics -lsfml-window -lsfml-system

build-server:
	g++ -g -Wuninitialized -o ./build/server ./src/server/*.cpp

clean:
	rm -f ./build/*
