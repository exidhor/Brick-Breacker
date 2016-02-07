 #pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "../header/Entity.h"

enum Cote {haut, bas, gauche, droit};

class Balle : public Entity
{
private:
	float m_directionX;
	float m_directionY;

	float m_angleX;
	float m_angleY;

	bool m_estEnCollision;

public:
	Balle();
	~Balle();

	void setVitesse(float newVitesse);

	void setDirectionX(float newDirectionX);
	void setDirectionY(float newDirectionY);
	
	void setAngleX(float newAngleX);
	void setAngleY(float newAngleY);

	void deplacement(float tempExec);

	bool collision(Entity* objet, float tempExec, bool find);

	void deplacementRebond(int distanceX, int distanceY);

	float distanceCentre(sf::FloatRect const& objet);

	sf::Vector2f calculEquationDroite(sf::Vector2f vertex1, sf::Vector2f vertex2);

	int calculDistanceReele(int distanceTotale, float vitesseObjet) const;
};