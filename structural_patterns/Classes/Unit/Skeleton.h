#ifndef GAME_SKELETON_H
#define GAME_SKELETON_H


#include "Unit.h"


class Skeleton: public Unit {
public:
	Skeleton(sf::RenderWindow & window, json & configs);;

	shared_ptr<Unit> Clone() const override;;

	void Draw() override {};

	string GetInfo() const override;;
};


#endif //GAME_SKELETON_H
