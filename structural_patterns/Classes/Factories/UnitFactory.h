#ifndef GAME_UNITFACTORY_H
#define GAME_UNITFACTORY_H


#include "IObject.h"
#include "Unit.h"
#include "Witch.h"
#include "Skeleton.h"


class UnitFactory: public IObject {
public:
	shared_ptr<Unit> Create(const pair<string, string> & id) {
		if (prototypes_.find(id) != prototypes_.end())
			return prototypes_[id]->Clone();
		else {
			SetError("Attempt to create a unit with an unknown id: " + id.first + ' ' + id.second);
			return nullptr;
		}
	};

	void Set(sf::RenderWindow &window, const string & filename) {
		Parser parser;
		map<string, json> units_prototypes = parser(filename);
		if (Parser::Error()) {
			SetError(Parser::GetLastError());
		}
		string unit_name;
		for (auto & prototype: units_prototypes) {
			unit_name = prototype.first;
			if (Parser::Error()) {
				SetError(Parser::GetLastError());
				continue;
			}
			if (prototype.second["Type"] == "Skeleton")
				prototypes_.emplace(make_pair("Skeleton", unit_name), shared_ptr<Unit>(new Skeleton(window, prototype.second["Configs_"])));
			if (prototype.second["Type"] == "Witch")
				prototypes_.emplace(make_pair("Witch", unit_name), shared_ptr<Unit>(new Witch(window, prototype.second["Configs_"])));
		}
	};

	virtual string GetInfo() const override {
		return IObject::GetInfo() + ", UnitFactory";
	};
private:
	map<pair<string, string>, shared_ptr<Unit>> prototypes_;
};


#endif //GAME_UNITFACTORY_H
