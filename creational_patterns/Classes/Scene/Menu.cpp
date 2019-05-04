#include "Menu.h"


Menu::Menu(sf::RenderWindow & window, const string & menu_name, const string & menu_resources): Scene(window) {
	Set(menu_name, menu_resources);
}

void Menu::Set(const string & menu_name, const string & menu_resources) {
	Parser parser;
	multimap<string, vector<string>> items_list = parser(menu_name);
	if (parser.Error())
		SetError(parser.GetLastError());
	ItemFactory item_factory;
	bool background_includes = false;
	for (auto & item: items_list) {
		shared_ptr<IMenuItem> ptr = item_factory.Create(GetWindow(), item.second[0], menu_resources + item.second[1]);
		if (item_factory.Error())
			SetError(item_factory.GetLastError());
		else
			items_.emplace(item.first, ptr);
	}
	//TODO: определить поведение для фона
//	if (background_includes) {
//		menu_file >> background_name;
//		SetBackGround(menu_resources + background_name);
//	}
}

void Menu::Draw() {
	GetWindow().draw(GetBackGround());
	for (auto item: GetItems())
		item.second->Draw();
}

string Menu::GetInfo() const {
	return Scene::GetInfo() + ", Menu";
}

const multimap<string, shared_ptr<IMenuItem>> & Menu::GetItems() const {
	return items_;
}

shared_ptr<Scene> MenuFactory::Create(sf::RenderWindow & window, const string & menu_name, const string & menu_resources) {
	shared_ptr<Menu> res = make_shared<Menu>(window, menu_name, menu_resources);
	if (res->Error())
		SetError(res->GetLastError());
	return res;
}

string MenuFactory::GetInfo() const {
	return SceneFactory::GetInfo() + ", MenuFactory";
}
