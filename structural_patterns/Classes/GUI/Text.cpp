#include "Text.h"

Text::Text(sf::RenderWindow & window, const json & configs) : IMenuItem(window), configs_(this) {
	if (configs.contains("Text"))
		configs_.SetText(configs["Text"], configs["Resources"]);
	if (configs.contains("Position")) {
		if (configs["Position"].size() != 3)
			SetError("An error occurred while trying to set the button position");
		else {
			body_.on_center = configs["Position"]["OnCenter"];
			configs_.SetPosition(configs["Position"]["X"], configs["Position"]["Y"]);
		}
	}
	if (configs.contains("ConstSize")) {
		body_.const_size = configs["ConstSize"];
	}
}

void Text::Draw() {
	GetWindow().draw(*body_.shape_);
	if (body_.const_size)
		configs_.SetScale(GetWindow().getView().getSize().x / GetWindow().getSize().x, GetWindow().getView().getSize().y / GetWindow().getSize().y);
	if (body_.on_center == true)
		configs_.SetPosition(GetWindow().getView().getCenter().x, GetWindow().getView().getCenter().y);
	GetWindow().draw(body_.text_);
}

void Text::Move(int x, int y) {
	body_.shape_->move(x, y);
}

string Text::GetInfo() const {
	return IEventObject::GetInfo() + ", Text";
}

void Text::SetField(pair<string, string> && _name_text) {
	for (auto & name_text: configs_.GetText())
		if (name_text.first == _name_text.first) {
			name_text.second = _name_text.second;
			configs_.SetText(configs_.GetText());
			return;
		}
}

string & Text::GetField(string & name) {
	for (auto & name_text: configs_.GetText())
		if (name_text.first == name)
			return name_text.second;
}

Text::Configs_::Configs_(Text * button) : text_(button) {}

void Text::Configs_::SetShape() {
	shared_ptr<sf::RectangleShape> new_shape = make_shared<sf::RectangleShape>(sf::Vector2f(text_->body_.text_.getGlobalBounds().width / text_->body_.shape_->getScale().x, text_->body_.text_.getGlobalBounds().height / text_->body_.shape_->getScale().y));
	new_shape->setFillColor(text_->body_.shape_->getFillColor());
	new_shape->setPosition(text_->body_.shape_->getPosition());
	text_->body_.shape_ = new_shape;
	text_->body_.width_ = text_->body_.text_.getGlobalBounds().width;
	text_->body_.height_ = text_->body_.text_.getGlobalBounds().height;
}

void Text::Configs_::SetColor(const json & color) {
	text_->body_.shape_->setFillColor(sf::Color(color["Red"], color["Green"], color["Blue"], color["Alpha"]));
}

void Text::Configs_::SetText(const json & text, const string & resources) {
	text_->body_.font_.loadFromFile(resources + string(text["Font"]));
	text_->body_.text_.setFont(text_->body_.font_);
	text_->body_.text_.setFillColor(sf::Color(text["Color"]["Red"], text["Color"]["Green"], text["Color"]["Blue"], text["Color"]["Alpha"]));
	string str;
	for (vector<string> name_string: text["Fields"]) {
		text_->body_.fields_.emplace_back(make_pair(name_string[0], name_string[1]));
		str += name_string[0] + ": " + name_string[1] + "\n";
	}
	text_->body_.text_.setString(str);
	text_->body_.text_.setCharacterSize(text["Size"]);

	text_->body_.shape_ = make_shared<sf::RectangleShape>(sf::Vector2f(text_->body_.text_.getGlobalBounds().width, text_->body_.text_.getGlobalBounds().height));
	SetShape();
	SetColor(text["BackGroundColor"]);
	//text_->body_.text_.setPosition(text_->body_.shape_->getPosition().x, text_->body_.shape_->getPosition().y);
}

void Text::Configs_::SetText(const vector<pair<string, string>> & fields) {
	string str = "";
	for (auto & field: fields)
		str += field.first + ": " + field.second + '\n';
	text_->body_.text_.setString(str);
	SetShape();
}

vector<pair<string, string>> & Text::Configs_::GetText() {
	return text_->body_.fields_;
}

void Text::Configs_::SetPosition(float x, float y) {
	text_->body_.text_.setPosition(x - text_->body_.text_.getGlobalBounds().width / 2, y - text_->body_.text_.getGlobalBounds().height / 2);
	text_->body_.shape_->setPosition(x - text_->body_.text_.getGlobalBounds().width / 2, y - text_->body_.text_.getGlobalBounds().height / 2);
}

void Text::Configs_::SetScale(float x, float y) {
	text_->body_.text_.setScale(x, y);
	text_->body_.shape_->setScale(x, y);
}
