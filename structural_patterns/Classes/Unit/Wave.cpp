#include "Wave.h"

Wave::Wave(sf::RenderWindow & window) : Unit(window) {}

void Wave::Draw() {
	for (auto & unit: units_) {
		unit->Draw();
	}
}

shared_ptr<Unit> Wave::Clone() const {
	Wave clone(GetWindow());
	for (auto & unit: units_) {
		clone.AddUnit(unit->Clone());
	}
	return make_shared<Wave>(clone);
}

void Wave::AddUnit(shared_ptr<Unit> && unit) {
	units_.push_back(unit);
}
