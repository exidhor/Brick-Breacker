#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "../header/Entity.h"

class Barre : public Entity
{
private:
	
public:
	Barre();
	~Barre();
	void setVitesse(float newVitesse);
	float getVitesse();
	void deplacement(int tempExec, int direction);
};