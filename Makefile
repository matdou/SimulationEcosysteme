main : main.cpp Aquarium.o Bestiole.o Milieu.o Peureux.o BestioleFactory.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o Peureux.o BestioleFactory.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Peureux.o : Peureux.h Peureux.cpp
	g++ -Wall -std=c++11  -c Peureux.cpp -I .

BestioleFactory.o : BestioleFactory.h BestioleFactory.cpp
	g++ -Wall -std=c++11  -c bestioleFactory.cpp -I .

clean:
	rm -rf *.o main

