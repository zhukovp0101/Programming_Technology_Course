#include "Button.h"

Button::ButtonInputHandler::ButtonInputHandler(Button * button) : InputHandler(button, button->GetWindow()) {
}

void
Button::ButtonInputHandler::MouseButtonPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	if (dynamic_cast<Button *>(event_object_)->ContainsPoint(event.mouseButton.x, event.mouseButton.y))
		(*command)(event);
}

Button::Button(sf::RenderWindow & window, const json & configs) : IMenuItem(window), configs_(this) {
	input_handler_ = make_shared<ButtonInputHandler>(this);
	input_handler_->Activate();
	if (!configs.contains("Shape")) {
		SetError("There is no button form in configs");
	}
	else {
		configs_.SetShape(configs["Shape"]);
	}

	if (configs.contains("Color"))
		configs_.SetColor(configs["Color"]);
	if (configs.contains("Text"))
		configs_.SetText(configs["Text"], configs["Resources"]);
	if (configs.contains("Position")) {
		if (configs["Position"].size() != 2)
			SetError("An error occurred while trying to set the button position");
		else configs_.SetPosition(configs["Position"]["X"], configs["Position"]["Y"]);
	}
}

void Button::Draw() {
	GetWindow().draw(*body_.shape_);
	GetWindow().draw(body_.text_);
}

void Button::Move(int x, int y) {
	body_.shape_->move(x, y);
}

string Button::GetInfo() const {
	return IEventObject::GetInfo() + ", Button";
}

bool Button::ContainsPoint(const int & x, const int & y) {
	if (body_.type_ == "Rectangle") {
		int realwidth =
				GetWindow().getSize().x / GetWindow().getView().getSize().x * body_.shape_->getGlobalBounds().width;
		int realheight =
				GetWindow().getSize().y / GetWindow().getView().getSize().y * body_.shape_->getGlobalBounds().height;
		sf::Rect<int> realrect(body_.shape_->getGlobalBounds().left, body_.shape_->getGlobalBounds().top, realwidth,
		                       realheight);
		return realrect.contains(x, y);
	}
	return false;
}

Button::Configs_::Configs_(Button * button) : button_(button) {}

void Button::Configs_::SetShape(const json & shape) {
	if (shape["Type"] == "Rectangle") {
		button_->body_.shape_ = make_shared<sf::RectangleShape>(sf::Vector2f(shape["Width"], shape["Height"]));
		button_->body_.width_ = shape["Width"];
		button_->body_.height_ = shape["Height"];
	}
	button_->body_.type_ = shape["Type"];
}

void Button::Configs_::SetColor(const json & color) {
	button_->body_.shape_->setFillColor(sf::Color(color["Red"], color["Green"], color["Blue"], color["Alpha"]));
}

void Button::Configs_::SetText(const json & text, const string & resources) {
	button_->body_.font_.loadFromFile(resources + string(text["Font"]));
	button_->body_.text_.setFont(button_->body_.font_);
	button_->body_.text_.setFillColor(sf::Color(text["Color"]["Red"], text["Color"]["Green"], text["Color"]["Blue"], text["Color"]["Alpha"]));
	button_->body_.text_.setString(string(text["String"]));
	button_->body_.text_.setCharacterSize(text["Size"]);

	button_->body_.text_.setPosition(button_->body_.shape_->getPosition().x + button_->body_.width_ / 2 - button_->body_.text_.getLocalBounds().width / 2 - button_->body_.text_.getLocalBounds().left / 2, button_->body_.shape_->getPosition().y + button_->body_.height_ / 2 - button_->body_.text_.getLocalBounds().height / 2 - button_->body_.text_.getLocalBounds().top);
}

void Button::Configs_::SetPosition(float x, float y) {
	button_->body_.text_.move(x - button_->body_.shape_->getPosition().x, y - button_->body_.shape_->getPosition().y);
	button_->body_.shape_->setPosition(x, y);
}


