#include "ItemFactory.h"

shared_ptr<IMenuItem> ItemFactory::Create(sf::RenderWindow & window, json & item) const {
	item["Configs"]["Resources"] = item["Resources"];
	if (item["Type"] == "Button")
		return shared_ptr<IMenuItem>(new Button(window, item["Configs"]));
	if (item["Type"] == "Text")
		return shared_ptr<IMenuItem>(new Text(window, item["Configs"]));
	else {
		SetError("The type of the element " + string(item["Type"]) + " does not match any of the valid types");
		return nullptr;
	}
}

string ItemFactory::GetInfo() const {
	return IObject::GetInfo() + ", ItemFactory";
}
