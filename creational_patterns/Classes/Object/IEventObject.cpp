#include "IEventObject.h"

IEventObject::IEventObject(sf::RenderWindow & window) : IDrawingObject(window) {

}

string IEventObject::GetInfo() const {
	return IDrawingObject::GetInfo() + ", IEventObject";
}

