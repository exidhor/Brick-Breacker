#include "../header/BestWindow.h"
#include "../header/Game.h"

int main()
{
	BestWindow* w = new BestWindow();
	Game game(w, 1, 2, 5);
	
	game.gameLoop();

	return 0;
}

//  g++ Balle.o main.o Game.o Brique.o Barre.o BestWindow.o -o main -BC:\Users\jipay\Documents\SFML-2.2\lib -lsfml-graphics -lsfml-window -lsfml-system