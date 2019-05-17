#ifndef GAME_TEXT_H
#define GAME_TEXT_H


#include "IMenuItem.h"
#include "Parser.h"
#include "BaseIncludes.h"


class Text: public IMenuItem {
public:
	explicit Text(sf::RenderWindow & window, const json & configs);;

	void Draw() override;

	void Move(int x, int y) override;

	virtual string GetInfo() const override;;

	void SetField(pair<string, string> && _name_text);

	string & GetField(string & name);

private:
	class Configs_ {
	public:
		explicit Configs_(Text * button);;
		void SetShape();
		void SetColor(const json & color);;
		void SetText(const json & text, const string & resources);;

		void SetText(const vector<pair<string, string>> & fields);

		vector<pair<string, string>> & GetText();

		void SetPosition(float x, float y);;

		void SetScale(float x, float y);

	private:
		Text * text_;
	};

	struct Body_ {
	public:
		shared_ptr<sf::Shape> shape_;
		vector<pair<string, string>> fields_;
		sf::Text text_;
		sf::Font font_;
		bool on_center = false;
		bool const_size = false;
		int width_ = 0;
		int height_ = 0;
	};

	Configs_ configs_;
	Body_ body_;
};


#endif //GAME_TEXT_H
