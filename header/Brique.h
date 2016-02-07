#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "../header/Entity.h"

class Brique : public Entity
{
private:
	unsigned int m_width;
	unsigned int m_height;

public:
	Brique();
	Brique(unsigned int width, unsigned int height);
	~Brique();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
	virtual int getOldPosX() const;
	virtual int getOldPosY() const;
};