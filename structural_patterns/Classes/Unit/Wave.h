#ifndef GAME_WAVE_H
#define GAME_WAVE_H

#include "BaseIncludes.h"
#include "Unit.h"


class Wave: public Unit {
public:
	explicit Wave(sf::RenderWindow & window);

	void Draw() override;

	shared_ptr<Unit> Clone() const override;

	void AddUnit(shared_ptr<Unit> && unit);

private:
	vector<shared_ptr<Unit>> units_;
};


#endif //GAME_WAVE_H
