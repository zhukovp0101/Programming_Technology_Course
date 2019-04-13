#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "IMenuItem.h"
#include "Parser.h"
#include "BaseIncludes.h"


class Button: public IMenuItem {
public:
	explicit Button(sf::RenderWindow & window, const json & configs): IMenuItem(window), configs_(this) {
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
	};
	void Draw() override {
		GetWindow().draw(*body_.shape_);
		GetWindow().draw(body_.text_);
	}
	virtual string GetInfo() const override {
		return IEventObject::GetInfo() + ", Button";
	};

private:
	class Configs_ {
	public:
		explicit Configs_(Button * button): button_(button) {};
		void SetShape(const json & shape) {
			if (shape["Type"] == "Rectangle") {
				button_->body_.shape_ = make_shared<sf::RectangleShape>(sf::Vector2f(shape["Width"], shape["Height"]));
				button_->body_.width_ = shape["Width"];
				button_->body_.height_ = shape["Height"];
			}
		};
		void SetColor(const json & color) {
			button_->body_.shape_->setFillColor(sf::Color(color["Red"], color["Green"], color["Blue"], color["Alpha"]));
		};
		void SetText(const json & text, const string & resources) {
			button_->body_.font_.loadFromFile(resources + string(text["Font"]));
			button_->body_.text_.setFont(button_->body_.font_);
			button_->body_.text_.setFillColor(sf::Color(text["Color"]["Red"], text["Color"]["Green"], text["Color"]["Blue"], text["Color"]["Alpha"]));
			button_->body_.text_.setString(string(text["String"]));
			button_->body_.text_.setCharacterSize(text["Size"]);

			button_->body_.text_.setPosition(button_->body_.shape_->getPosition().x + button_->body_.width_ / 2 - button_->body_.text_.getLocalBounds().width / 2 - button_->body_.text_.getLocalBounds().left / 2, button_->body_.shape_->getPosition().y + button_->body_.height_ / 2 - button_->body_.text_.getLocalBounds().height / 2 - button_->body_.text_.getLocalBounds().top);
		};
		void SetOnClick(){}; // TODO: определить поведение;
		void SetPosition(float x, float y) {
			button_->body_.text_.move(x - button_->body_.shape_->getPosition().x, y - button_->body_.shape_->getPosition().y);
			button_->body_.shape_->setPosition(x, y);
		};

	private:
		Button * button_;
	};

	struct Body_ {
	public:
		shared_ptr<sf::Shape> shape_;
		sf::Text text_;
		sf::Font font_;
		int width_ = 0;
		int height_ = 0;
	};

	Configs_ configs_;
	Body_ body_;
};


#endif //GAME_BUTTON_H
