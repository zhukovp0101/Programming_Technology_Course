#include "UnitFactory.h"

shared_ptr<Unit> UnitFactory::Create(const pair<string, string> & id) {
	if (prototypes_.find(id) != prototypes_.end())
		return prototypes_[id]->Clone();
	else {
		SetError("Attempt to create a unit with an unknown id: " + id.first + ' ' + id.second);
		return nullptr;
	}
}

void UnitFactory::Set(sf::RenderWindow & window, const string & filename) {
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
			prototypes_.emplace(make_pair("Skeleton", unit_name), shared_ptr<Unit>(new Skeleton(window, prototype.second["Configs"])));
		if (prototype.second["Type"] == "Witch")
			prototypes_.emplace(make_pair("Witch", unit_name), shared_ptr<Unit>(new Witch(window, prototype.second["Configs"])));
	}
}

string UnitFactory::GetInfo() const {
	return IObject::GetInfo() + ", UnitFactory";
}
