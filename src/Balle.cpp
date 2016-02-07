#include "../header/Balle.h"

Balle::Balle() 
	: Entity(0.0004), m_directionX(1), m_directionY(1),
   	 m_angleX(0), m_angleY(0), m_estEnCollision(false)
{
	sf::Texture tmp;
	if(!tmp.loadFromFile("../img/newBalle.png"))
	{
		std::cout << "ERROR WHILE LOADING BALLE TEXTURE" << std::endl;
	}
	m_texture = new sf::Texture(tmp);
	setTexture(*m_texture);
 	//setTextureRect(sf::IntRect(0, 0, 20, 20));
 	setColor(sf::Color(255, 255, 255, 255));
}

Balle::~Balle()
{
	delete m_texture;
	m_texture = 0;
}

void Balle::setVitesse(float newVitesse)
	{ m_vitesse =  newVitesse; }

void Balle::setDirectionX(float newDirectionX)
	{ m_directionX = newDirectionX; }

void Balle::setDirectionY(float newDirectionY)
	{ m_directionY = newDirectionY; }

void Balle::setAngleX(float newAngleX)
	{ m_angleX = newAngleX; }

void Balle::setAngleY(float newAngleY)
	{ m_angleY = newAngleY; }

void Balle::deplacement(float tempExec)
{
	//distance parcouru en un tour de GameLoop est d'environ 3
	//avec une vitesse de 0.0002 et un tempExec de 15000
	//move((int)(m_vitesse*m_directionX*tempExec), (int)(m_vitesse*m_directionY*tempExec));
	move(6*m_directionX, 6*m_directionY);

	//on trace la trajectoire en partant du centre de l'objet.
	//si cela coupe une brique, on place la balle sur la brique
}

// le 3e param est un retour pour le redecalage de la balle sur la surface
// de l'objet percuté
bool Balle::collision(Entity* objet, float tempExec, bool p_find)
{
	/*etude de la trajectoire de la balle par rapport aux parois de l'objet
	I est l'ancien point (top-left), J est l'actuel point(top-left)
	
	-verification de la collision(standart)
	-on retrace la trajectoire parcouru par la balle(avec un pas de 1)
		jusqu'a arrivé sur l'un des cotés de l'objet
	-suivant le coté, on calcul le rebond
	*/
	//s'il y a collision
	
	if(getGlobalBounds().intersects(objet->getGlobalBounds()))
	{
		if(!p_find)
		{
			//on part de J
			std::cout << "collision";
			int posX = getGlobalBounds().left;
			int posY = getGlobalBounds().top;

			//on retrace la trajectoire parcouru par la balle(avec un pas de 1)
			//jusqu'a arrivé sur l'un des cotés de l'objet
			bool find = false;

			//distance de penetration
			int distance;

			while(!find)
			{
				//on fait reculer les coordonnées
				posX += -m_directionX;
				posY += -m_directionY;

				if(posX == objet->getGlobalBounds().left - getGlobalBounds().width)
				{
					find = true;
					m_directionX = -1;

					distance = getGlobalBounds().left - posX;
					//on remet posY a la position actuelle de la balle
					//pour ne pas a avoir a recalculer le deplacement en Y
					posY = getGlobalBounds().top;

					setPosition(posX, posY);
					deplacementRebond((-1)*calculDistanceReele(distance, objet->getVitesse()), 0);
				}

				else if(posX == objet->getGlobalBounds().left + objet->getGlobalBounds().width)
				{
					find = true;
					m_directionX = 1;
					distance = posX - getGlobalBounds().left;
					posY = getGlobalBounds().top;

					setPosition(posX, posY);
					deplacementRebond(calculDistanceReele(distance, objet->getVitesse()), 0);

				}

				else if(posY == objet->getGlobalBounds().top - getGlobalBounds().height)
				{
					find = true;
					m_directionY = -1;
					distance = getGlobalBounds().top - posY;
					posX = getGlobalBounds().left;

					setPosition(posX, posY);
					deplacementRebond(0, (-1)*calculDistanceReele(distance, objet->getVitesse()));
				}

				else if(posY == objet->getGlobalBounds().top + objet->getGlobalBounds().height)
				{
					find = true;
					m_directionY = 1;
					distance =  posY - getGlobalBounds().top;
					posX = getGlobalBounds().left;

					setPosition(posX, posY);
					deplacementRebond(0, calculDistanceReele(distance, objet->getVitesse()));
				}
			}
		}
		

		return true;
	}

	return false;
}

float Balle::distanceCentre(sf::FloatRect const& objet)
{
	float xd = getGlobalBounds().left + getGlobalBounds().width * 1/2 - objet.left + objet.width * 1/2;
	float yd = getGlobalBounds().top + getGlobalBounds().height * 1/2 - objet.top + objet.height * 1/2;

	return sqrt(xd * xd + yd * yd);
}

sf::Vector2f Balle::calculEquationDroite(sf::Vector2f vertex1, sf::Vector2f vertex2)
{
	float pente = (vertex2.y - vertex1.y) / (vertex2.x - vertex1.x);
	float ordonnee = vertex1.y - pente * vertex1.x;

	return sf::Vector2f(pente, ordonnee);
}

int Balle::calculDistanceReele(int distanceTotale, float vitesseObjet) const
{
	if(vitesseObjet > m_vitesse)
		return (m_vitesse / vitesseObjet) * distanceTotale;
	else
		return (vitesseObjet / m_vitesse) * distanceTotale;
}

void Balle::deplacementRebond(int distanceX, int distanceY)
{
	//TO DO
	move(distanceX, distanceY);
}


//g++ Balle.cpp -c -IC:\Users\jipay\Documents\SFML-2.2\include
//g++ Balle.o -o BestWindow -BC:\Users\jipay\Documents\SFML-2.2\lib -lsfml-graphics -lsfml-window -lsfml-system

