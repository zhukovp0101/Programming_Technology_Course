#include "Level.h"


Level::Level(sf::RenderWindow & window, const string & filename) : Scene(window), IEventObject(window), map_(window) {
	Set(filename);
	input_handler_->SetCommand(sf::Event::MouseWheelScrolled, make_shared<Scroll>(this));
	input_handler_->SetCommand(sf::Event::KeyPressed, make_shared<KeyPressed>(this));
	input_handler_->SetCommand(sf::Event::KeyReleased, make_shared<KeyReleased>(this));
	input_handler_->SetCommand(sf::Event::MouseMoved, make_shared<MouseMoved>(this));
	input_handler_->SetCommand(sf::Event::MouseButtonPressed, make_shared<MouseButtonPressed>(this));
	view_ = GetWindow().getView();
}

void Level::Draw() {
	if (IsActiveNow()) {
		GetWindow().draw(GetBackGround());
		map_.Draw();
		for (auto & tower_ptr: towers_ptrs_) {
			tower_ptr->Draw();
		}
	}
}

sf::Vector2u Level::GetSize() const {
	return map_.GetSize();
}

void Level::Set(const string & filename) {
	map<string, json> configs = Parser::File_To_Json(filename);
	configs["Map"]["Resources"] = configs["Resources"];
	map_.Set(configs["Map"]);
	tower_factory_.Set(GetWindow(), configs["TowersConfigs"]);
	if (Map::Error())
		SetError(Map::GetLastError());
}

string Level::GetInfo() const {
	return Scene::GetInfo() + ", Level";
}

void Level::Activate() {
	view_.setCenter(GetSize().x / 2, GetSize().y / 2);
	view_.setSize(GetSize().x, GetSize().y);
	GetWindow().setView(view_);
	active_now_ = true;
	GetInputHandler().Activate();
}

void Level::Deactivate() {
	active_now_ = false;
	GetInputHandler().Deactivate();
}

void Level::Update() {
	if (IsActiveNow()) {
		if (moving_now_) {
			SmartMove();
		}
	}
}

void Level::AddTower(const string & tower_type, int x, int y) {
	towers_ptrs_.push_back(tower_factory_.Create(tower_type));
	towers_ptrs_[towers_ptrs_.size() - 1]->SetPosition(x, y);
}

void Level::SmartMove() {
	if (view_.getCenter().x - view_.getSize().x / 2 + speed_.x * moving_x_ >= 0 &&
	    view_.getCenter().x + view_.getSize().x / 2 + speed_.x * moving_x_ <= GetSize().x)
		view_.move(speed_.x * moving_x_, 0);
	if (view_.getCenter().y - view_.getSize().y / 2 + speed_.y * moving_y_ >= 0 &&
	    view_.getCenter().y + view_.getSize().y / 2 + speed_.y * moving_y_ <= GetSize().y)
		view_.move(0, speed_.y * moving_y_);

	GetWindow().setView(view_);
}

Level::Scroll::Scroll(Level * level) : level_(level) {
}

const void Level::Scroll::operator ()(const sf::Event & event) {
	float delta;
	if (event.mouseWheelScroll.delta > 0)
		delta = event.mouseWheelScroll.delta / 10 + 1;
	else
		delta = 1 / (-event.mouseWheelScroll.delta / 10 + 1);
	level_->view_.zoom(1 / delta);
	while (level_->view_.getCenter().x + level_->view_.getSize().x / 2 > level_->GetSize().x)
		level_->view_.move(-10, 0);
	while (level_->view_.getCenter().x - level_->view_.getSize().x / 2 < 0)
		level_->view_.move(10, 0);
	while (level_->view_.getCenter().y + level_->view_.getSize().y / 2 > level_->GetSize().y)
		level_->view_.move(0, -10);
	while (level_->view_.getCenter().y - level_->view_.getSize().y / 2 < 0)
		level_->view_.move(0, 10);
	if (level_->view_.getSize().x > level_->GetSize().x || level_->view_.getSize().y > level_->GetSize().y) {
		level_->view_.setCenter(level_->GetSize().x / 2, level_->GetSize().y / 2);
		level_->view_.setSize(level_->GetSize().x, level_->GetSize().y);
	}
//			level_->speed_ = {level_->GetSize().x / level_->view_.getSize().x * level_->min_speed_.x, level_->GetSize().y / level_->view_.getSize().y * level_->min_speed_.y};
	level_->GetWindow().setView(level_->view_);
}

Level::KeyPressed::KeyPressed(Level * level) : level_(level) {}

const void Level::KeyPressed::operator ()(const sf::Event & event) {
	switch (event.key.code) {
		case sf::Keyboard::A:
			level_->moving_x_ = -1;
			break;
		case sf::Keyboard::D:
			level_->moving_x_ = 1;
			break;
		case sf::Keyboard::S:
			level_->moving_y_ = 1;
			break;
		case sf::Keyboard::W:
			level_->moving_y_ = -1;
			break;
	}
	level_->moving_now_ = true;
}

Level::KeyReleased::KeyReleased(Level * level) : level_(level) {}

const void Level::KeyReleased::operator ()(const sf::Event & event) {
	switch (event.key.code) {
		case sf::Keyboard::A:
			level_->moving_x_ = 0;
			break;
		case sf::Keyboard::D:
			level_->moving_x_ = 0;
			break;
		case sf::Keyboard::S:
			level_->moving_y_ = 0;
			break;
		case sf::Keyboard::W:
			level_->moving_y_ = 0;
			break;
	}
	level_->moving_now_ = true;
}

Level::MouseMoved::MouseMoved(Level * level) : level_(level) {}

const void Level::MouseMoved::operator ()(const sf::Event & event) {
	for (auto & tower_ptr: level_->towers_ptrs_) {
		tower_ptr->GetInputHandler()(event);
	}
}

Level::MouseButtonPressed::MouseButtonPressed(Level * level) : level_(level) {}

const void Level::MouseButtonPressed::operator ()(const sf::Event & event) {
	for (auto & tower_ptr: level_->towers_ptrs_) {
		tower_ptr->GetInputHandler()(event);
	}
}
