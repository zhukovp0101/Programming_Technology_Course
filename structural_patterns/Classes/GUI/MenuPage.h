#ifndef GAME_MENUPAGE_H
#define GAME_MENUPAGE_H


#include "BaseIncludes.h"
#include "Parser.h"
#include "Scene.h"
#include "IMenuItem.h"
#include "ItemFactory.h"

class MenuPage: public Scene {
public:
	MenuPage() = delete;
	MenuPage(sf::RenderWindow &window, const json &page_name);;

	void Draw() override;;

	void Set(const json &configs);;

	map<pair<string, string>, shared_ptr<IMenuItem>> & GetItems();;

	string GetInfo() const override;;

	void Move(int x, int y);

	sf::Vector2u GetSize() const override;

private:
	map<pair<string, string>, shared_ptr<IMenuItem>> items_;
};


#endif //GAME_MENUPAGE_H
