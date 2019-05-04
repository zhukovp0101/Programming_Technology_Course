#include "IMenuItem.h"

IMenuItem::IMenuItem(sf::RenderWindow & window) : IEventObject(window) {

}

string IMenuItem::GetInfo() {
	return IEventObject::GetInfo() + ", IMenuItem";
}
