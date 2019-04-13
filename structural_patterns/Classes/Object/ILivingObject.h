#ifndef GAME_ILIVINGOBJECT_H
#define GAME_ILIVINGOBJECT_H


#include "IObject.h"
#include "BaseIncludes.h"


class ILivingObject: public IDrawingObject {
public:
	explicit ILivingObject(sf::RenderWindow & window): IDrawingObject(window) {};
	virtual ~ILivingObject() = default;
	virtual void Draw() override = 0;
	virtual string GetInfo() const override {
		return IDrawingObject::GetInfo() + ", ILivingObject";
	};

};


#endif //GAME_ILIVINGOBJECT_H
