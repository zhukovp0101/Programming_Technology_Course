#ifndef GAME_IBUILDING_H
#define GAME_IBUILDING_H


#include "ILivingObject.h"
#include "BaseIncludes.h"


class IBuilding: public ILivingObject {
public:
	explicit IBuilding(sf::RenderWindow & window): ILivingObject(window) {};
	virtual string GetInfo() const override {
		return ILivingObject::GetInfo() + ", IBuilding";
	};
};


#endif //GAME_IBUILDING_H
