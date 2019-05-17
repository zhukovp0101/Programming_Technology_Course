#ifndef GAME_TOWERFACTORY_H
#define GAME_TOWERFACTORY_H

#include "IObject.h"
#include "Tower.h"
#include "Unit.h"


class TowerFactory: public IObject {
public:
	shared_ptr<Tower> Create(const string & id);;

	void Set(sf::RenderWindow &window, const string & filename);;

	virtual string GetInfo() const override;;
private:
	class TowerPrototype {
	public:
		TowerPrototype(sf::RenderWindow & window, string & tower_type, json & configs);
		shared_ptr<Tower> Clone();
	private:
		shared_ptr<Tower> tower_ptr_;
	};
	map<string, shared_ptr<TowerPrototype>> prototypes_ptrs_;
};


#endif //GAME_TOWERFACTORY_H
