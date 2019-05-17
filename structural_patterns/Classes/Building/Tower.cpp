#include "Tower.h"

Tower::Tower(sf::RenderWindow & window, json & configs) : IEventObject(window), ILivingObject(window, configs) {
	improvements_configs_ptr_ = make_shared<vector<TowerConfigs>>(configs["Improvements"].size());
	for (int i = 0; i < configs["Improvements"].size(); ++i) {
		(*improvements_configs_ptr_)[i].texture_.loadFromFile(string(configs["Resources"]) + string(configs["Improvements"][i]["Texture"]));
		(*improvements_configs_ptr_)[i].height = configs["Improvements"][i]["Height"];
		(*improvements_configs_ptr_)[i].width = configs["Improvements"][i]["Width"];
		(*improvements_configs_ptr_)[i].max_health = configs["Improvements"][i]["Health"];
		json bullet_configs(configs["Improvements"][i]["Bullet"]);
		bullet_configs["Texture"] = string(configs["Resources"]) + string(bullet_configs["Texture"]);
		(*improvements_configs_ptr_)[i].bullet_configs_ = BulletConfigs(bullet_configs);
	}
	selection_menu_ptr_ = make_shared<SelectionMenu>(window, this, string(configs["Resources"]) + string(configs["SelectionMenu"]));
}

Tower::Tower(const Tower & copy) : IEventObject(copy.GetWindow()), ILivingObject(copy) {
	improvements_configs_ptr_ = copy.improvements_configs_ptr_;
	selection_menu_ptr_ = make_shared<SelectionMenu>(*copy.selection_menu_ptr_, this);
	input_handler_->Activate();
	input_handler_->SetCommand(sf::Event::MouseMoved, make_shared<MouseMoved>(this));
	input_handler_->SetCommand(sf::Event::MouseButtonPressed, make_shared<MouseButtonPressed>(this));
	sprite_.setTexture(improvements_configs_ptr_->at(0).texture_);
}

shared_ptr<Tower> Tower::Clone() {
	return make_shared<Tower>(*this);
}

void Tower::Draw() {
	//cout << sprite_.getPosition().x << ' ' << sprite_.getPosition().y;
	GetWindow().draw(sprite_);
	selection_menu_ptr_->Draw();
}

void Tower::SetPosition(int x, int y) {
	sprite_.setPosition(x, y);
}

void Tower::ActivateSelection() {
	active_selection_now_ = true;
	selection_menu_ptr_->Activate();
}

void Tower::DeactivateSelection() {
	active_selection_now_ = false;
	selection_menu_ptr_->Deactivate();
}

bool Tower::ContainsPoint(const int & x, const int & y) {
	int realwidth = sprite_.getTextureRect().width;
	int realheight = sprite_.getTextureRect().height;
	int view_x = GetWindow().getView().getCenter().x - GetWindow().getView().getSize().x / 2;
	int view_y = GetWindow().getView().getCenter().y - GetWindow().getView().getSize().y / 2;
	int x_length = x * GetWindow().getView().getSize().x / GetWindow().getSize().x;
	int y_length = y * GetWindow().getView().getSize().y / GetWindow().getSize().y;

	sf::Rect<int> realrect(sprite_.getGlobalBounds().left, sprite_.getGlobalBounds().top, realwidth, realheight);
	return realrect.contains(x_length + view_x, y_length + view_y);
}

Tower::SelectionMenu::SelectionMenu(sf::RenderWindow & window, Tower * tower, const string & filename) : IMenu(window, filename),
                                                                                                         tower_(tower), filename_(filename) {}

Tower::SelectionMenu::SelectionMenu(const Tower::SelectionMenu & copy, Tower * tower) : IMenu(copy.GetWindow(), copy.filename_), tower_(tower), filename_(copy.filename_) {

}

Tower::MouseButtonPressed::MouseButtonPressed(Tower * tower) : tower_(tower) {}

const void Tower::MouseButtonPressed::operator ()(const sf::Event & event) {
	if (tower_->active_selection_now_) {
		++tower_->current_level_;
		shared_ptr<Text> properties = dynamic_pointer_cast<Text>(tower_->selection_menu_ptr_->GetPages()["Main"]->GetItems()[make_pair("Text", "Text")]);
		properties->SetField(make_pair("Level", to_string(tower_->current_level_)));
	}
}

Tower::BulletConfigs::BulletConfigs(json & configs) {
	damage = configs["Damage"];
	texture_.loadFromFile(configs["Texture"]);
}

WatchTower::WatchTower(sf::RenderWindow & window, json & configs) : Tower(window, configs){
}
