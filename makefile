sfml-app : main.o game.o 
	g++ main.o game.o -o sfml-app -std=c++11 -L /home/pierre/SFML/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o : main.cpp game.cpp game.h
	g++ -c main.cpp game.cpp -std=c++11 -I /home/pierre/SFML/include

clean :
	rm sfml-app *.o
