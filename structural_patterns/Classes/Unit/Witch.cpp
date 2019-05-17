#include "Witch.h"

Witch::Witch(sf::RenderWindow & window, json & configs) : Unit(window) {}

shared_ptr<Unit> Witch::Clone() const {
	return shared_ptr<Unit>(new Witch(*this));
}

string Witch::GetInfo() const {
	return Unit::GetInfo() + ", Witch";
}
