#ifndef GAME_IEVENTOBJECT_H
#define GAME_IEVENTOBJECT_H


#include "IObject.h"
#include "BaseIncludes.h"


class IEventObject: public IDrawingObject {
public:
	explicit IEventObject(sf::RenderWindow & window): IDrawingObject(window) {};
	virtual ~IEventObject() = default;
	virtual void Draw() override = 0;
	virtual string GetInfo() const override {
		return IDrawingObject::GetInfo() + ", IEventObject";
	};
};





#endif //GAME_IEVENTOBJECT_H
