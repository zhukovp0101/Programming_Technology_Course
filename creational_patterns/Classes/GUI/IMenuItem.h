#ifndef GAME_IMENUITEM_H
#define GAME_IMENUITEM_H


#include "IEventObject.h"
#include "BaseIncludes.h"


class IMenuItem: public IEventObject {
public:
	explicit IMenuItem(sf::RenderWindow & window);
	virtual ~IMenuItem() = default;
	virtual void Draw() override = 0;
	virtual string GetInfo();
};


#endif //GAME_IMENUITEM_H
