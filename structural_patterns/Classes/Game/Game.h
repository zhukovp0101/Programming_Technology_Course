#ifndef GAME_GAME_H
#define GAME_GAME_H


#include "BaseIncludes.h"
#include "IMenu.h"
#include "Level.h"

class Game: IDrawingObject {
public:
	Game(sf::RenderWindow & window, const string & mainmenu_filename, const string & mainlevel_filename);;
	void Run();
	void Draw() override {};

private:
	class MainMenu: public IMenu {
	public:
		MainMenu(sf::RenderWindow & window, Game * game, const string & filename);;

		Game * game_;
	private:
		class MainPage {
		public:
			explicit MainPage(MainMenu * menu);

		private:
			class RunCommand: public Command<sf::Event> {
			public:
				explicit RunCommand(Game * game);;
				const void operator ()(const sf::Event & event) override;
			private:
				Game * game_;
			};

			void SetCommands();;

			MainMenu * menu_;
		};
	};

	MainMenu main_menu_;
	Level main_level_;
};


#endif //GAME_GAME_H
