#include "../header/Game.h"

Game::Game(BestWindow* window)
	: m_score(10000), m_vies(1), m_gameOver(false), m_window(window)
{
	m_balle = new Balle();
	m_barre = new Barre();

	//TO DO
	m_briques.push_back(std::vector <Brique*>() );
	m_briques[0].push_back(new Brique());
}

Game::Game(BestWindow* window, int vie)
	:m_score(10000), m_vies(vie), m_gameOver(false), m_window(window)
{
	m_balle = new Balle();
	m_barre = new Barre();
	//TO DO
	m_briques.push_back(std::vector<Brique*>() );
	m_briques[0].push_back(new Brique());
}

Game::Game(BestWindow* window, int vie, int nb_colonne, int nb_ligne)
	:m_score(10000), m_vies(vie), m_gameOver(false), m_window(window)
{
	m_balle = new Balle();
	m_barre = new Barre();
	m_barre->setPosition((m_window->getWidth()-120)/2, (m_window->getHeight()-15)*9/10);
	//std::cout << m_barre->getVitesse() << std::endl;

	int tailleX = 40;
	int tailleY = 40;

	//distance entre les briques et le mur
	int distanceX = (m_window->getWidth() - nb_ligne*tailleX)/2;
	int distanceY = (m_window->getHeight() - nb_colonne*tailleY) /3;

	std::cout << "Window : width : " << m_window->getWidth() << " height : " << m_window->getHeight() << std::endl;
	std::cout << "distanceX = " << distanceX << std::endl;
	std::cout << "(" << m_window->getWidth() << "-" <<  nb_colonne << "*" << tailleX << ")" << "/2" << std::endl;

	for(int i = 0; i < nb_ligne; ++i)
	{
		m_briques.push_back(std::vector <Brique*>() );

		for(int j = 0; j < nb_colonne; ++j)
		{
			m_briques[i].push_back(new Brique(tailleX, tailleY));
			m_briques[i][j]->setPosition(distanceX+i*tailleX, distanceY+j*tailleY);
		}
	}

	sf::Texture* tmp = new sf::Texture();
	if(!tmp->loadFromFile("../img/background_dark.png"))
	{
		std::cout << "ERROR WHILE LOADING BALLE TEXTURE" << std::endl;
	}
	//sf::Texture* m_texture = new sf::Texture(tmp);
	sf::Texture* m_texture = new sf::Texture(*tmp);
	m_background.setTexture(*m_texture);
 	//setTextureRect(sf::IntRect(0, 0, 20, 20));
 	m_background.setColor(sf::Color(255, 255, 255, 255));

}

Game::~Game()
{
	delete m_balle;
	m_balle = 0;

	delete m_barre;
	m_barre = 0;

	//destruction des briques
	for(int i = 0; i < m_briques.size(); ++i)
	{
		for(int j = 0; j < m_briques[i].size(); ++j)
		{
			delete m_briques[i][j];
			m_briques[i][j] = 0;
		}
	}
	delete m_background.getTexture();
	//m_background = 0;
}

/* Boucle principale qui represente une partie
*/
void Game::gameLoop()
{
	sf::Event event;
	float tempPause;
	sf::Clock clock;
	float tempFrame = (1./60) * 1000000;

	while(m_window->isOpen())
	{
		//debut du chrono du tempExec
		//clock.restart().asMicroseconds();

		//recupération des entrées
		gestionEntree(event, 15000);
		
		//deplacement de la balle et gestion des collisions
		deplacementBalle(15000);

		//std::cout << "sortie" << std::endl;	

		tempPause = tempFrame - clock.getElapsedTime().asMicroseconds();
		sf::sleep(sf::microseconds(tempPause));

		/*while(tempPause < tempFrame - 650)
	    {
	    	//std::cout << tempPause << "  ";
	      	tempPause = clock.getElapsedTime().asMicroseconds();
	    }*/
	   	
	   	//clear + draw + display
		affichage();
	}
}

/* Cette methode recupere les entrées claviers et
les gerent en consequence
*/
void Game::gestionEntree(sf::Event & event, float tempExec)
{
	while(m_window->pollEvent(event))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_window->close();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//std::cout << "deplacement" << std::endl;
		m_barre->deplacement(tempExec, -1);
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//std::cout << "deplacement" << std::endl;
		m_barre->deplacement(tempExec, 1);
	}
}

/*L'affichage se fait en 3 etapes obligatoires
-La premiere consiste a "vider" le contenu de la fenetre
-Puis on dessine tous les objets
-Enfin on affiche le rendu
*/
void Game::affichage() const
{
	//1ere etape
	m_window->clear();

	m_window->draw(m_background);

	//2e etape
	m_window->draw(*m_balle);
	m_window->draw(*m_barre);
	
	for(int i = 0; i < m_briques.size(); ++i)
	{
		for(int j = 0; j < m_briques[i].size(); ++j)
		{
			if(m_briques[i][j] != 0)
				m_window->draw(*m_briques[i][j]);
		}
	}

	//3e etape
	m_window->display();
}

void Game::deplacementBalle(float tempExec)
{
	m_balle->deplacement(tempExec);

	//calcul des collisions
	gestionCollisions(tempExec);
}

void Game::gestionCollisions(float tempExec)
{
	/*verification du contact :
		-avec les murs
		-avec le curseur
		-avec les briques
	La gestion des collisions continue dans les fonctions appelées
	*/
	if(collisionMurBalle())
	{

	}

	else if(collisionBarreBalle(tempExec))
	{

	}

	else if(collisionBriquesBalle(tempExec))
	{

	}
}

bool Game::collisionMurBalle()
{
	//si la balle touche le mur du haut
	if(m_balle->getGlobalBounds().top <= 0)
	{
		m_balle->setDirectionY(1);
		return true;
	}
	//si la balle touche le mur du bas
	else if(m_balle->getGlobalBounds().top +
		m_balle->getGlobalBounds().height >= m_window->getHeight())
	{
		m_window->close();
		m_balle->setDirectionY(-1);
		return true;
	}
	//si la balle touche le mur de gauche
	else if(m_balle->getGlobalBounds().left <= 0)
	{
		m_balle->setDirectionX(1);
		return true;
	}
	//si la balle touche le mur de droite
	else if(m_balle->getGlobalBounds().left + 
		m_balle->getGlobalBounds().width >= m_window->getWidth())
	{
		m_balle->setDirectionX(-1);
		return true;
	}
	return false;
}

bool Game::collisionBarreBalle(float tempExec)
{
	if(m_balle->collision(m_barre, tempExec, false))
		return true;

	return false;
}

bool Game::collisionBriquesBalle(float tempExec)
{
	std::vector <Brique**> objets;
	bool find = false;
	//parcours du vector
	for(int i = 0; i < m_briques.size(); ++i)
	{
		for(int j = 0; j < m_briques[i].size(); ++j)
		{
			//verification que l'objet existe
			if(m_briques[i][j] != 0)
			{
				if(m_balle->getGlobalBounds().intersects(m_briques[i][j]->getGlobalBounds()))
				{
					if(!find)
						find = true;
					objets.push_back(&m_briques[i][j]);
					//destruction de la brique touchée
					//delete m_briques[i][j];
					//m_briques[i][j] = 0;
					//return true;
				}
			}
		}
	}
	if(objets.size() == 0)
		return false;

	int indice = 0;
	float distanceLaPlusCourte = m_balle->distanceCentre((*objets[0])->getGlobalBounds() );
	float distanceTest;
	for(int i = 1; i < objets.size(); i++)
	{
		distanceTest = m_balle->distanceCentre((*objets[i])->getGlobalBounds() );
		if(distanceLaPlusCourte > distanceTest)
		{
			indice = i;
		}
	}

	m_balle->collision(*objets[indice], 0, false);


	//std::cout << "destruction" << std::endl;
	//destruction de la brique touchée
	delete *objets[indice];
	//std::cout << "0" << std::endl;
	(*objets[indice]) = 0;
	return true;
}

//g++ Game.cpp -c -IC:\Users\jipay\Documents\SFML-2.2\include