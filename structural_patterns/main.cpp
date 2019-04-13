//#include "BaseTestIncludes.h"
#include <LevelFactory.h>
#include "BaseIncludes.h"
#include "MenuFactory.h"


int main(int argc, char *argv[]) {
	//setenv("DISPLAY", "127.0.0.1:0", true);
////	::testing::InitGoogleTest(&argc, argv);
////	return RUN_ALL_TESTS();
	sf::RenderWindow app(sf::VideoMode(500, 500), "Tower Defense!");
	app.setFramerateLimit(60);
	sf::View view = app.getView();

//	MenuFactory menu_factory;
//	auto menu = menu_factory.Create(app, "Resources/Scenes/Menu/initial_menu.txt");

	LevelFactory level_factory;
	auto level = level_factory.Create(app, "Resources/Scenes/Levels/Level_1/level.json");
	view.setCenter(level->GetSize().x/2, level->GetSize().y/2);
	view.zoom(5);
	app.setView(view);

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.clear();
		level->Draw();
		app.display();
	}
}