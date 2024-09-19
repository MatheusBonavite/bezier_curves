.PHONY: bezier clear

bezier: main.o
	g++-12 main.o -lSDL2 -o bezier

main.o: main.cpp
	g++-12 --std=c++23 -c -I/usr/include/SDL2 main.cpp

clear:
	rm -rf *.o
	rm -rf bezier
