#ifndef GAME_ITEMFACTORY_H
#define GAME_ITEMFACTORY_H


#include "IObject.h"
#include "IMenuItem.h"
#include "Button.h"
#include "BaseIncludes.h"


class ItemFactory: public IObject {
public:
	shared_ptr<IMenuItem> Create(sf::RenderWindow & window, json & item) const {
		item["Configs"]["Resources"] = item["Resources"];
		if (item["Type"] == "Button")
			return shared_ptr<IMenuItem>(new Button(window, item["Configs"]));
		else {
			SetError("The type of the element " + string(item["Type"]) + " does not match any of the valid types");
			return nullptr;
		}
	};

	string GetInfo() const override {
		return IObject::GetInfo() + ", ItemFactory";
	};
};


#endif //GAME_ITEMFACTORY_H
