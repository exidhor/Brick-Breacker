#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

class BestWindow : public sf::RenderWindow
{
private:
	unsigned int m_width;
	unsigned int m_height;
public:
	BestWindow();
	BestWindow(unsigned int width, unsigned int height);
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);

	unsigned int getWidth() const;
	unsigned int getHeight() const;
};