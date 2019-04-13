#ifndef GAME_WITCH_H
#define GAME_WITCH_H


#include "Unit.h"


class Witch: public Unit {
public:
	Witch(sf::RenderWindow & window, json & configs): Unit(window) {};

	shared_ptr<Unit> Clone() const override {
		return shared_ptr<Unit>(new Witch(*this));
	};

	void Draw() override {};

	string GetInfo() const override {
		return Unit::GetInfo() + ", Witch";
	};
};


#endif //GAME_WITCH_H
