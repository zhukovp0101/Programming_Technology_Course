#ifndef GAME_CASTLE_H
#define GAME_CASTLE_H


#include "IBuilding.h"
#include "BaseIncludes.h"


class Castle: public IBuilding {
public:
	explicit Castle(sf::RenderWindow & window): IBuilding(window) {};
	virtual string GetInfo() const override {
		return IBuilding::GetInfo() + ", Castle";
	};
};


#endif //GAME_CASTLE_H
