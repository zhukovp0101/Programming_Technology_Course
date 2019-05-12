#include "Unit.h"

Unit::Unit(sf::RenderWindow & window) : ILivingObject(window) {}

string Unit::GetInfo() const {
	return ILivingObject::GetInfo() + ", Unit";;
}
