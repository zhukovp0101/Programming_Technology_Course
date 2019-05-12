#include "Skeleton.h"

Skeleton::Skeleton(sf::RenderWindow & window, json & configs) : Unit(window) {}

shared_ptr<Unit> Skeleton::Clone() const {
	return shared_ptr<Unit>(new Skeleton(*this));
}

string Skeleton::GetInfo() const {
	return Unit::GetInfo() + ", Skeleton";
}
