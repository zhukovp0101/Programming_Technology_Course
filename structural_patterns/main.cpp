//#include "BaseTestIncludes.h"
#include "Level.h"
#include "BaseIncludes.h"
#include "IMenu.h"
#include "Game.h"


int main(int argc, char *argv[]) {
	sf::RenderWindow app(sf::VideoMode(1000, 1000), "Tower Defense!");

	Game game(app, "Resources/Scenes/Menu/initial_menu.txt", "Resources/Scenes/Levels/Level_1/level.json");
	game.Run();
}