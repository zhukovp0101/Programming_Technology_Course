#include "IMenu.h"

IMenu::IMenuInputHandler::IMenuInputHandler(IMenu * menu_object) : InputHandler(menu_object, menu_object->GetWindow()) {
}

void IMenu::IMenuInputHandler::Catch_(const sf::Event & event) {
	for (auto & page: dynamic_cast<IMenu *>(event_object_)->GetPages()) {
		if (page.second->IsActiveNow()) {
			for (auto & name_item: page.second->GetItems())
				name_item.second->GetInputHandler()(event);
		}
	}
}

IMenu::IMenu(sf::RenderWindow & window, const string & menu_name) : IEventObject(window), Scene(window) {
	input_handler_ = make_shared<IMenuInputHandler>(this);
	Set(menu_name);
}

void IMenu::Deactivate() {
	GetInputHandler().Deactivate();
	active_now_ = false;
}

void IMenu::Activate() {
	active_now_ = true;
	GetInputHandler().Activate();
}

void IMenu::Draw() {
	if (IsActiveNow())
		pages_[active_page_]->Draw();
}

void IMenu::Set(const string & filename) {
	json configs = Parser::File_To_Json(filename);
	for (auto & page_configs: Parser::Json_To_Map(configs["Pages"])) {
		pages_.emplace(page_configs.first, make_shared<MenuPage>(Scene::GetWindow(), page_configs.second));
	}
	pages_["Main"]->Activate();
}

void IMenu::Move(int x, int y) {
	for (auto & page_ptr: pages_) {
		page_ptr.second->Move(x, y);
	}
}

map<string, shared_ptr<MenuPage>> & IMenu::GetPages() {
	return pages_;
}

string IMenu::GetInfo() const {
	return IEventObject::GetInfo() + ", IMenu";
}
