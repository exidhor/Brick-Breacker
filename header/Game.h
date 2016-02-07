#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "../header/Balle.h"
#include "../header/Barre.h"
#include "../header/Brique.h"
#include "../header/BestWindow.h"

class Game
{
private:
	Balle* m_balle;
	Barre* m_barre;
	std::vector <std::vector <Brique*> > m_briques;
	int m_score;
	int m_vies;
	bool m_gameOver;
	sf::Sprite m_background;

	BestWindow* m_window;

public:
	Game(BestWindow* window);
	Game(BestWindow* window, int vie);
	Game(BestWindow* window, int vie, int nb_colonne, int nb_ligne);
	~Game();
	void gameLoop();
	void gestionEntree(sf::Event & event, float tempExec);
	void affichage() const;
	void gestionCollisions(float tempExec);
	void deplacementBalle(float tempExec);
	bool collisionMurBalle();
	bool collisionBarreBalle(float tempExec);
	bool collisionBriquesBalle(float tempExec);
};