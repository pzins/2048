#include "game.h"
#include <ctime>
#define WIDTH_CASE 64
#define HEIGHT_CASE 64

#define NB_CASE 12 //0,2,4,8,16,32,64,128,256,512,1024,2048
#define SIZE 4	//carre 4x4


Game::Game(int w, int h) : app(sf::VideoMode(w, h), "2048", sf::Style::Default)
{
	screen_ = {{2,0,0,1,},{0,0,0,0},{0,1,0,0},{0,0,0,4}};
}


Game::~Game()
{

}


/**
* chargement des textures et sprites
* text_vect : vecteur contenant 12 textures : 0 à 11
* double boucle sur la matrice screen_ pour afficher chaque case (en créant une sprite à partir d'une texture)
*/
void Game::drawMap()
{
    std::vector<sf::Texture> text_vect;
    for (int i = 0; i < NB_CASE; ++i)
    {
        sf::Texture perso;
        std::string namefile = "NB/" + std::to_string(i) + ".png";
        perso.loadFromFile(namefile);
        perso.setSmooth(true);
        text_vect.push_back(perso);
    }
   
    for (int i = 0; i < screen_.size(); ++i)
    {
        for (int j = 0; j < screen_[i].size(); ++j)
        {
            sf::Sprite sprite;
            sprite.setTexture(text_vect[screen_[i][j]]);
            sprite.setPosition(sf::Vector2f(j * WIDTH_CASE,i * HEIGHT_CASE));
            app.draw(sprite); 
        }
    }
}

/**
* Mouvement vers le haut (fleche haut)
*/
void Game::moveUp()
{
	bool has_move = false; //si il y a eu un mouvement, pr afficher une nouvelle case ou nn
	int x;
	for (int j = 0; j < SIZE; ++j)	//boucle sur chaque colonne de 0 à 3
	{
		int corr = 0;	//eviter qu'une nvelle case fusion de 2 autres soit refusionner encore une fois pr un seul mouvement
		for (int i = 1; i < SIZE; ++i)	//boucle sur chaque ligne sauf la première car ces cases ne peuvent pas bouger
		{
			if (screen_[i][j]) //si la case n'est pas vide
			{
				bool deplacement = false;
				x = i-1;
				while (x > 0 + corr && screen_[x][j] == 0) //passent ttes les cases vides
				{
					x--;
					deplacement = true;
				}
				//x : ligne ou on a une case nn vide que l'on pourra ou nn fusionner
				//ou ligne la plus haute et la case est vide dc on peut faire monter la case jusqu'en haut

				//la case n'est pas vide et nn fusionnable avec notre case [i][j]
				//mais on a que des 0 entre
				//dc on prend la case précedente (ici +1) et on inverse les cases
				if (deplacement && screen_[x][j] && screen_[x][j] != screen_[i][j])
				{
					screen_[x+1][j] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				//si la case est vide (forcement la case la plus haut ici je crois) on inverse simplement
				else if (screen_[x][j] == 0)
				{
					screen_[x][j] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				//sinon les 2 cases sont fusionnables (à nouveau que des 0 entre)
				else if (screen_[x][j] == screen_[i][j])
				{
					screen_[x][j]++;
					screen_[i][j] = 0;
					has_move = true;
				}
				//on boucle sur ttes les cases de cette colonnes en commençant par le début (ici les cases les plus hautes)
			}	
		}
	}
	//si il y a eu un mouvement -> on crée une nouvelle case
	if (has_move) newCase();
}

/**
* Mouvement vers le bas (fleche bas)
*/
void Game::moveDown()
{
	bool has_move = false;
	int x;
	for (int j = 0; j < SIZE; ++j)
	{
		int corr = 0;
		for (int i = SIZE - 2; i >= 0; --i)
		{
			if (screen_[i][j])
			{
				bool deplacement = false;
				x = i+1;
				while (x < 3 && x > corr && screen_[x][j] == 0)
				{
					x++;
					deplacement = true;
				}
				if (deplacement && screen_[x][j] && screen_[x][j] != screen_[i][j])
				{
					screen_[x-1][j] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				else if (screen_[x][j] == 0)
				{
					screen_[x][j] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				else if (screen_[x][j] == screen_[i][j])
				{
					screen_[x][j]++;
					screen_[i][j] = 0;
					++corr;
					has_move = true;
				}						
			}	
		}
	}
	if (has_move) newCase();
}


/**
* Mouvement vers la gauche (fleche gauche)
*/
void Game::moveLeft()
{
	bool has_move = false;
	int y;
	for (int i = 0; i < SIZE; ++i)
	{
		int corr = 0;
		for (int j = 1; j < SIZE; ++j)
		{
			if (screen_[i][j])
			{
				bool deplacement = false;
				y = j-1;
				while (y > 0 + corr && screen_[i][y] == 0)
				{
					y--;
					deplacement = true;
				}
				if (deplacement && screen_[i][y] && screen_[i][y] != screen_[i][j])
				{
					screen_[i][y+1] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				if (screen_[i][y] == 0)
				{
					screen_[i][y] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				else if (screen_[i][y] == screen_[i][j])
				{
					screen_[i][y]++;
					screen_[i][j] = 0;
					has_move = true;
				}
							
			}	
		}
	}
	if (has_move) newCase();
}


/**
* Mouvement vers la droite (fleche droite)
*/
void Game::moveRight()
{
	bool has_move = false;
	int y;
	for (int i = 0; i < SIZE; ++i)
	{
		int corr = 0;
		for (int j = SIZE - 2; j >= 0; --j)
		{
			if (screen_[i][j])
			{
				bool deplacement = false;
				y = j+1;
				while (y < 3 && y > corr && screen_[i][y] == 0)
				{
					y++;
					deplacement = true;
				}
				if (deplacement && screen_[i][y] && screen_[i][y] != screen_[i][j])
				{
					screen_[i][y-1] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				if (screen_[i][y] == 0)
				{
					screen_[i][y] = screen_[i][j];
					screen_[i][j] = 0;
					has_move = true;
				}
				else if (screen_[i][y] == screen_[i][j])
				{
					screen_[i][y]++;
					screen_[i][j] = 0;
					has_move = true;
					++corr;
				}
							
			}	
		}
	}
	if (has_move) newCase();
}

/*
* creation d'une nouvelle case : 2 ou 4 (pourcentage 2/3, 1/3)
* à la place d'une case vide de manière aléatoire
*/ 
void Game::newCase()
{
    srand (time(NULL));
    int x,y;
    do
    {
    	x = rand() % SIZE;
    	y = rand() % SIZE;
    }
    while (screen_[x][y]);
    int choice = rand() % 10;
    if (choice > 3)
    {
    	screen_[x][y] = 1;
    }
    else screen_[x][y] = 2;
}

/*
* fct qui vérifie si le joueur a perdu ou si il a gagné
*/
void Game::verify()
{
	sf::Font font;

	bool game_over = true;
	bool win = false;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			 //si une case est vide ou 2 cases voisines st fusionnables (horiz ou vert) -> pas perdu
			if ((!screen_[i][j])
			|| (j < SIZE - 1 && screen_[i][j] == screen_[i][j+1])
			|| (i < SIZE - 1 && screen_[i][j] == screen_[i+1][j])) game_over = false;
			if (screen_[i][j] == NB_CASE - 1) win = true; //si une case contient 2048 (12ème tile) -> gagné
		}
	}
	//affichage victoire
	if (win)
	{
		font.loadFromFile("arial.ttf");
		sf::Text text;
		text.setFont(font);
		text.setString("Congratulations You Win !!!");
		text.setCharacterSize(38);
		text.setPosition(sf::Vector2f(20,100));
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Red);
		app.draw(text);
	}
	//affichage défaite
	else if (game_over)
	{
		font.loadFromFile("arial.ttf");
		sf::Text text;
		text.setFont(font);
		text.setString("Game Over");
		text.setCharacterSize(38);
		text.setPosition(sf::Vector2f(20,100));
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Red);
		app.draw(text);
	}
}

