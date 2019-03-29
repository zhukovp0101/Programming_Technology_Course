#include "ItemFactory.h"

shared_ptr<IMenuItem> ItemFactory::Create(sf::RenderWindow & window, const string & item_type, const string & filename) {
	if (item_type == "Button")
		return shared_ptr<IMenuItem>(new Button(window, filename));
	else {
		SetError("The type of the element "+ item_type +" does not match any of the valid types");
		return nullptr;
	}
}

string ItemFactory::GetInfo() const {
	return IObject::GetInfo() + ", ItemFactory";
}
