#ifndef GAME_IMENUITEM_H
#define GAME_IMENUITEM_H


#include "IEventObject.h"
#include "BaseIncludes.h"


class IMenuItem: public IEventObject, public IDrawingObject {
public:
	explicit IMenuItem(sf::RenderWindow & window): IDrawingObject(window), IEventObject(window) {
	};
	virtual ~IMenuItem() = default;
	virtual void Draw() = 0;
	virtual void Move(int x, int y) = 0;
	virtual string GetInfo() {return IEventObject::GetInfo() + ", IMenuItem";};
};


#endif //GAME_IMENUITEM_H
