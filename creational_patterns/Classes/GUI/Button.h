#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "IMenuItem.h"
#include "Parser.h"
#include "BaseIncludes.h"


class Button: public IMenuItem {
public:
	explicit Button(sf::RenderWindow & window, const string & settings_name);
	void Draw() override;
	virtual string GetInfo() const override;

private:
	class Settings {
	public:
		explicit Settings(Button * button);
		void SetShape(vector<string> & shape);
		void SetColor(vector<string> & color);
		void SetText(vector<string> & text);
		void SetOnClick(){}; // TODO: определить поведение;
		void SetPosition(float x, float y);

	private:
		Button * button_;
	};

	Settings settings_;

	shared_ptr<sf::Shape> body_;
};


#endif //GAME_BUTTON_H
