#include "../header/Entity.h"

Entity::Entity(float vitesse)
	: sf::Sprite(), m_vitesse(vitesse), m_posOldX(1), m_posOldY(1), m_texture(0)
{

}

Entity::~Entity()
{
	delete m_texture;
	m_texture = 0;
}

/*int Entity::getPosOldX() const
	{ return m_posOldX; }

int Entity::getPosOldY() const
	{ return m_posOldY; }
*/
float Entity::getVitesse() const
	{ return m_vitesse; }