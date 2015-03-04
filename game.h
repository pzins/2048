#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>




class Game
{
private:
	    std::vector<std::vector<int> > screen_;



public:
    sf::RenderWindow app;


	Game(int w, int h);
	~Game();

	void drawMap();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void newCase();
	void verify();



};

























#endif 