#include "Castle.h"

Castle::Castle(sf::RenderWindow &window): IBuilding(window) {

}

string Castle::GetInfo() const {
	return IBuilding::GetInfo() + ", Castle";
}
