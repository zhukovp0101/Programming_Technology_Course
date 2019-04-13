#ifndef GAME_SKELETON_H
#define GAME_SKELETON_H


#include "Unit.h"


class Skeleton: public Unit {
public:
	Skeleton(sf::RenderWindow & window, json & configs): Unit(window) {};

	shared_ptr<Unit> Clone() const override {
		return shared_ptr<Unit>(new Skeleton(*this));
	};

	void Draw() override {};

	string GetInfo() const override {
		return Unit::GetInfo() + ", Skeleton";
	};
};


#endif //GAME_SKELETON_H
