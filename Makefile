.PHONY: bezier clear

bezier: main.o
	g++ main.o -lSDL2 -o bezier

main.o: main.cpp
	g++ --std=c++17 -c -I/usr/include/SDL2 main.cpp

clear:
	rm -rf *.o
	rm -rf bezier
