#ifndef GAME_ITEMFACTORY_H
#define GAME_ITEMFACTORY_H


#include "IObject.h"
#include "IMenuItem.h"
#include "Button.h"
#include "Text.h"
#include "BaseIncludes.h"


class ItemFactory: public IObject {
public:
	shared_ptr<IMenuItem> Create(sf::RenderWindow & window, json & item) const;;

	string GetInfo() const override;;
};


#endif //GAME_ITEMFACTORY_H
