#ifndef GAME_MENU_H
#define GAME_MENU_H


#include "Scene.h"
#include "IMenuItem.h"
#include "ItemFactory.h"
#include "BaseIncludes.h"
#include "Parser.h"


class Menu: public Scene {
public:
	Menu() = delete;
	Menu(sf::RenderWindow &window, const string &menu_name, const string &menu_resources);

	void Draw() override;

	void Set(const string &menu_name, const string &menu_resources);

	const multimap<string, shared_ptr<IMenuItem>> & GetItems() const;

	virtual string GetInfo() const override;

private:
	multimap<string, shared_ptr<IMenuItem>> items_;
};




class MenuFactory: public SceneFactory {
public:
	shared_ptr<Scene> Create(sf::RenderWindow &window, const string &menu_name, const string &menu_resources);
	virtual string GetInfo() const override;
};


#endif //GAME_MENU_H
