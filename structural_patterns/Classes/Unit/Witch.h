#ifndef GAME_WITCH_H
#define GAME_WITCH_H


#include "Unit.h"


class Witch: public Unit {
public:
	Witch(sf::RenderWindow & window, json & configs);;

	shared_ptr<Unit> Clone() const override;;

	void Draw() override {};

	string GetInfo() const override;;
};


#endif //GAME_WITCH_H
