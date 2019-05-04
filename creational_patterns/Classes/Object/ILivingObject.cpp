#include "ILivingObject.h"

ILivingObject::ILivingObject(sf::RenderWindow &window): IDrawingObject(window) {

}

string ILivingObject::GetInfo() const {
	return IDrawingObject::GetInfo() + ", ILivingObject";
}


