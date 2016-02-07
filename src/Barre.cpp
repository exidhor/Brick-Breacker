#include "../header/Barre.h"

Barre::Barre()
	: Entity(0.001)
{
	//, m_vitesse(0.0003)
	//m_texture = new sf::Texture();
	//std::cout << "vitesse barre : " << m_vitesse << std::endl;
	sf::Texture tmp;
	if(!tmp.loadFromFile("../img/barre_flamme.png"))
	{
		std::cout << "ERROR WHILE LOADING BALLE TEXTURE" << std::endl;
	}
	m_texture = new sf::Texture(tmp);
	setTexture(*m_texture);
 	//setTextureRect(sf::IntRect(0, 0, 20, 20));
 	setColor(sf::Color(255, 255, 255, 255));
}

Barre::~Barre()
{
	delete m_texture;
	m_texture = 0;
}

void Barre::setVitesse(float newVitesse)
	{ m_vitesse = newVitesse;}

float Barre::getVitesse()
	{ return m_vitesse; }

void Barre::deplacement(int tempExec, int direction)
{
	//std::cout << "tempExec = " << tempExec << std::endl;
	//std::cout << "m_vitesse = " << m_vitesse << std::endl;
	//std::cout << "direction = " << direction << std::endl;
	move((int)(tempExec*m_vitesse*direction), 0);
}