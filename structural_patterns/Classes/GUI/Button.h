#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "IMenuItem.h"
#include "Parser.h"
#include "BaseIncludes.h"


class Button: public IMenuItem {
public:
	class ButtonInputHandler: public InputHandler {
	public:
		explicit ButtonInputHandler(Button * button);
	protected:
		void MouseButtonPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) override;
	};

	explicit Button(sf::RenderWindow & window, const json & configs);;

	void Draw() override;

	void Move(int x, int y) override;

	virtual string GetInfo() const override;;

protected:
	virtual bool ContainsPoint(const int & x, const int & y);

private:
	class Configs_ {
	public:
		explicit Configs_(Button * button);;
		void SetShape(const json & shape);;
		void SetColor(const json & color);;
		void SetText(const json & text, const string & resources);;
		void SetPosition(float x, float y);;

	private:
		Button * button_;
	};

	struct Body_ {
	public:
		shared_ptr<sf::Shape> shape_;
		string type_ = "";
		sf::Text text_;
		sf::Font font_;
		int width_ = 0;
		int height_ = 0;
	};

	Configs_ configs_;
	Body_ body_;
};


#endif //GAME_BUTTON_H
