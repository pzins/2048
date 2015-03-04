#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>

#include <string>
#include <fstream>
 
#include "game.h"

#define WIDTH_SCREEN 360
#define HEIGTH_SCREEN 208

#define NB_BLOCS_LARGEUR 15
#define NB_BLOCKS_HAUTEUR 13

#define LARGEUR_TILE 24  
#define HAUTEUR_TILE 16 

void drawMap(Game* game, std::string name);

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
                    
            }
        }

        drawMap(game, "map.txt");
            
        game->app.display();
        game->app.clear();
    }

    return 0;
}





void drawMap(Game* game, std::string name)
{
    std::vector<sf::Texture> text_vect;
    std::vector<sf::Sprite> sprite_vect;
    for (int i = 0; i < 8; ++i)
    {
        sf::Texture perso;
        perso.loadFromFile("0.bmp", sf::IntRect(24 * i, 0, 24, 16));
        perso.setSmooth(true);
        text_vect.push_back(perso);
    }
    std::ifstream fichier(name, std::ios::in); 
    if (fichier)
    {
        std::string contenu;    
        int line = 0;
        while( getline(fichier, contenu))
        {
            for (int i = 0; i < contenu.size(); ++i)
            {
                sf::Sprite sprite;
                sprite.setTexture(text_vect[int(contenu[i])-48]);
                sprite.setPosition(sf::Vector2f(i * 24,line * 16));
                game->app.draw(sprite); 
            }
            std::cout << std::endl;
            ++line;             
        }
        fichier.close();
    }
    else std::cout << "ERROR : open file    \n";
}
