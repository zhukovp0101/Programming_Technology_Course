#include "MenuPage.h"

MenuPage::MenuPage(sf::RenderWindow & window, const json & page_name) : Scene(window) {
	Set(page_name);
}

void MenuPage::Draw() {
	GetWindow().draw(GetBackGround());
	for (auto & item: GetItems())
		item.second->Draw();
}

void MenuPage::Set(const json & configs) {
	if (configs.contains("BackGround"))
		SetBackGround(string(configs["Resources"]) + string(configs["BackGround"]));
	ItemFactory item_factory;
	for (auto & item: Parser::Json_To_Map(configs["Items"])) {
		item.second["Resources"] = configs["Resources"];
		shared_ptr<IMenuItem> ptr = item_factory.Create(GetWindow(), item.second);
		items_.emplace(make_pair(item.second["Type"], item.first), ptr);
	}
}

map<pair<string, string>, shared_ptr<IMenuItem>> & MenuPage::GetItems() {
	return items_;
}

string MenuPage::GetInfo() const {
	return Scene::GetInfo() + ", IMenu";
}

void MenuPage::Move(int x, int y) {
	for (auto & item_ptr: items_) {
		item_ptr.second->Move(x, y);
	}
}

sf::Vector2u MenuPage::GetSize() const {
	return GetWindow().getSize();
}
