#include "IBuilding.h"

IBuilding::IBuilding(sf::RenderWindow &window) : ILivingObject(window) {

}

string IBuilding::GetInfo() const {
	return ILivingObject::GetInfo() + ", IBuilding";
}
