#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include <string>
 
#include "game.h"

#define WIDTH_SCREEN 256
#define HEIGTH_SCREEN 256




void drawMap(Game* game, std::vector<std::vector<int> > screen);

int main()
{
    Game* game = new Game(WIDTH_SCREEN, HEIGTH_SCREEN);

    while (game->app.isOpen())
    {
        sf::Event event;
        while (game->app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game->app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    game->moveUp();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    game->moveDown();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    game->moveLeft();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    game->moveRight();
                }  
            }
        }


        game->drawMap();
        game->verify();
        game->app.display();
        game->app.clear();
    }

    return 0;
}



