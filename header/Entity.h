#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

class Entity : public sf::Sprite
{
protected:
	sf::Texture* m_texture;
	float m_vitesse;
	int m_posOldX;
	int m_posOldY;

public:
	Entity(float vitesse);
	~Entity();
	//virtual int getPosOldX() const;
	//virtual int getPosOldY() const;
	float getVitesse() const;
};