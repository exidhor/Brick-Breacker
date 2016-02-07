#include "../header/Brique.h"

Brique::Brique()
	: Entity(0), m_width(30), m_height(30)
{
	m_texture = new sf::Texture();
	setTexture(*m_texture);

 	setTextureRect(sf::IntRect(300, 300, 30, 30));
 	setColor(sf::Color(255, 255, 255, 200));
}

Brique::Brique(unsigned int width, unsigned int height)
	: Entity(0), m_width(width), m_height(height)
{
	sf::Texture tmp;
	if(!tmp.loadFromFile("../img/brique.png"))
	{
		std::cout << "ERROR WHILE LOADING BALLE TEXTURE" << std::endl;
	}
	m_texture = new sf::Texture(tmp);
	setTexture(*m_texture);
 	//setTextureRect(sf::IntRect(0, 0, 20, 20));
 	setColor(sf::Color(255, 255, 255, 255));
}

Brique::~Brique()
{
	delete m_texture;
	m_texture = 0;
}

void Brique::setWidth(unsigned int newWidth)
	{ m_width = newWidth; }

void Brique::setHeight(unsigned int newHeight)
	{ m_height = newHeight; }

unsigned int Brique::getWidth() const
	{ return m_width; }

unsigned int Brique::getHeight() const
	{ return m_height; }

//l'objet etant inanimé, son ancienne position est egale
//a son actuelle position
int Brique::getOldPosX() const
	{ return getGlobalBounds().left; }

int Brique::getOldPosY() const
	{ return getGlobalBounds().top; }