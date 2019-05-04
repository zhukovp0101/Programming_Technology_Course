#include "Button.h"


Button::Button(sf::RenderWindow & window, const string & filename): IMenuItem(window), settings_(this) {
	Parser parser;
	multimap<string, vector<string>> settings = parser(filename);
	if (parser.Error()) {
		SetError(parser.GetLastError());
	}
	if (settings.find("Shape") == settings.end()) {
		SetError("There is no button form in the file " + filename);
	}
	else {
		settings_.SetShape(settings.find("Shape")->second);
	}
	for (auto & setting: settings) {
		if (setting.first == "Color")
			settings_.SetColor(setting.second);
		if (setting.first == "Text")
			settings_.SetText(setting.second);
		if (setting.first == "Position") {
			float x, y;
			if (setting.second.size() != 2) {
				SetError("An error occurred while trying to set the button position, file: " + filename);
				continue;
			}
			settings_.SetPosition(parser.To_Int(setting.second[0]), parser.To_Int(setting.second[1]));
		}
	}
}

void Button::Draw() {
	GetWindow().draw(*body_);
}

string Button::GetInfo() const {
	return IEventObject::GetInfo() + ", Button";
}

Button::Settings::Settings(Button * button): button_(button) {
}

void Button::Settings::SetShape(vector<string> & shape) {
	if (shape[0] == "Rectangle")
		button_->body_ = make_shared<sf::RectangleShape>(sf::Vector2f(50, 50));
}

void Button::Settings::SetColor(vector<string> & color) {

}

void Button::Settings::SetText(vector<string> & text) {

}

void Button::Settings::SetPosition(float x, float y) {
	this->button_->body_->setPosition(x, y);
}
