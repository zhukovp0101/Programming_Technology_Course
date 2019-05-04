#ifndef GAME_WARRIOR_H
#define GAME_WARRIOR_H


#include "Parser.h"
#include "ILivingObject.h"
#include "BaseIncludes.h"


class Unit: public ILivingObject {
public:
	explicit Unit(sf::RenderWindow & window);

	virtual shared_ptr<Unit> Clone() const = 0;

	virtual void Draw() = 0;

	virtual string GetInfo() const override;
};

class Skeleton: public Unit {
public:
	Skeleton(sf::RenderWindow & window, string setting_name, string settings_resources);

	virtual shared_ptr<Unit> Clone() const override;

	void Draw() override;

	virtual string GetInfo() const override;
};

class Witch: public Unit {
public:
	Witch(sf::RenderWindow & window, string setting_name, string settings_resources);

	virtual shared_ptr<Unit> Clone() const override;

	void Draw() override;

	virtual string GetInfo() const override;
};




class UnitFactory: public IObject {
public:
	shared_ptr<Unit> Create(pair<string, int> id);

	void Set(sf::RenderWindow &window, const string & settings_name, const string & settings_resources);

	virtual string GetInfo() const override;
private:
	map<pair<string, int>, shared_ptr<Unit>> prototypes_;
};


#endif //GAME_WARRIOR_H