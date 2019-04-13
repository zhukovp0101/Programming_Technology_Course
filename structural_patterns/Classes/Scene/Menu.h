#ifndef GAME_MENU_H
#define GAME_MENU_H


#include "Scene.h"
#include "IMenuItem.h"
#include "Factories/ItemFactory.h"
#include "BaseIncludes.h"
#include "Parser.h"


class Menu: public Scene {
public:
	Menu() = delete;
	Menu(sf::RenderWindow &window, const string &menu_name): Scene(window) {
		Set(menu_name);
	};

	void Draw() override {
		GetWindow().draw(GetBackGround());
		for (auto & item: GetItems())
			item.second->Draw();
	};

	void Set(const string &filename) {
		json configs = Parser::File_To_Json(filename);
		if (configs.contains("BackGround"))
			SetBackGround(string(configs["Resources"]) + string(configs["BackGround"]));
		ItemFactory item_factory;
		for (auto & item: Parser::Json_To_Map(configs["Items"])) {
			item.second["Resources"] = configs["Resources"];
			shared_ptr<IMenuItem> ptr = item_factory.Create(GetWindow(), item.second);
			items_.emplace(make_pair(item.second["Type"], item.first), ptr);
		}
	};

	const multimap<pair<string, string>, shared_ptr<IMenuItem>> & GetItems() const {
		return items_;
	};

	string GetInfo() const override {
		return Scene::GetInfo() + ", Menu";
	};

	sf::Vector2u GetSize() const override {
		return GetWindow().getSize();
	}

private:
	multimap<pair<string, string>, shared_ptr<IMenuItem>> items_;
};


#endif //GAME_MENU_H
