#ifndef GAME_WARRIOR_H
#define GAME_WARRIOR_H


#include "Parser.h"
#include "ILivingObject.h"
#include "BaseIncludes.h"


class Unit: public ILivingObject {
public:
	explicit Unit(sf::RenderWindow & window);;

	virtual shared_ptr<Unit> Clone() const = 0;

	virtual void Draw() = 0;

	string GetInfo() const override;;
};


#endif //GAME_WARRIOR_H