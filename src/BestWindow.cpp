#include "../header/BestWindow.h"

BestWindow::BestWindow()
	: sf::RenderWindow(sf::VideoMode(800, 600), "My window", 0), m_width(800), m_height(600)
{
	setFramerateLimit(60);
}

BestWindow::BestWindow(unsigned int width, unsigned int height)
	: sf::RenderWindow(sf::VideoMode(width, height), "My window", 0), m_width(width), m_height(height)
{
	setFramerateLimit(60);
}

void BestWindow::setWidth(unsigned int newWidth)
	{ m_width = newWidth; }

void BestWindow::setHeight(unsigned int newHeight)
	{ m_height = newHeight; }

unsigned int BestWindow::getWidth() const
	{ return m_width; }

unsigned int BestWindow::getHeight() const
	{ return m_height; }