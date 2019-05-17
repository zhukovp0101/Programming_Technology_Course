#include "Game.h"

Game::Game(sf::RenderWindow & window, const string & mainmenu_filename, const string & mainlevel_filename) : IDrawingObject(window), main_menu_(window, this, mainmenu_filename), main_level_(window, mainlevel_filename) {
	main_menu_.Activate();
	for (int i = 0; i < 100; ++i) {
		main_level_.AddTower("WatchTower", 500, i * 200);
	}
}

void Game::Run() {
	while (GetWindow().isOpen()) {
		sf::Event event;
		while (GetWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				GetWindow().close();
//				//if (event.type == sf::Event::KeyPressed)
//					main_menu_.GetInputHandler()(event);
			//if (event.type == sf::Event::MouseButtonPressed
			main_menu_.GetInputHandler()(event);
			main_level_.GetInputHandler()(event);
		}

		main_level_.Update();

		GetWindow().clear();
		main_menu_.Draw();
		main_level_.Draw();
		GetWindow().display();
	}
}

Game::MainMenu::MainMenu(sf::RenderWindow & window, Game * game, const string & filename) : IMenu(window, filename), game_(game) {
	MainPage main_page(this);
}

Game::MainMenu::MainPage::MainPage(Game::MainMenu * menu) : menu_(menu) {
	SetCommands();
}

void Game::MainMenu::MainPage::SetCommands() {
	menu_->GetPages()["Main"]->GetItems()[make_pair("Button", "Run")]->GetInputHandler().SetCommand(sf::Event::MouseButtonPressed, make_shared<RunCommand>(menu_->game_));
}

Game::MainMenu::MainPage::RunCommand::RunCommand(Game * game) : game_(game) {}

const void Game::MainMenu::MainPage::RunCommand::operator ()(const sf::Event & event) {
	game_->main_menu_.Deactivate();
	game_->main_level_.Activate();
}
