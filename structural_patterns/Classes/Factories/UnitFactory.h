#ifndef GAME_UNITFACTORY_H
#define GAME_UNITFACTORY_H


#include "IObject.h"
#include "Unit.h"
#include "Witch.h"
#include "Skeleton.h"


class UnitFactory: public IObject {
public:
	shared_ptr<Unit> Create(const pair<string, string> & id);;

	void Set(sf::RenderWindow &window, const string & filename);;

	virtual string GetInfo() const override;;
private:
	map<pair<string, string>, shared_ptr<Unit>> prototypes_;
};


#endif //GAME_UNITFACTORY_H
