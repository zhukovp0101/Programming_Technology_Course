#include "TowerFactory.h"

shared_ptr<Tower> TowerFactory::Create(const string & id) {
	if (prototypes_ptrs_.find(id) != prototypes_ptrs_.end())
		return prototypes_ptrs_[id]->Clone();
	else {
		SetError("Attempt to create a tower with an unknown type: " + id);
		return nullptr;
	}
}

void TowerFactory::Set(sf::RenderWindow & window, const string & filename) {
	map<string, json> configs = Parser::File_To_Map(filename);
	if (Parser::Error()) {
		SetError(Parser::GetLastError());
	}
	string tower_type;
	for (auto & prototype: Parser::Json_To_Map(configs["Prototypes"])) {
		tower_type = prototype.first;
		if (Parser::Error()) {
			SetError(Parser::GetLastError());
			continue;
		}
		prototype.second["Resources"] = string(configs["Resources"]) + string(prototype.second["Resources"]);
		prototypes_ptrs_.emplace(tower_type, make_shared<TowerPrototype>(window, tower_type, prototype.second));
	}
}

string TowerFactory::GetInfo() const {
	return IObject::GetInfo() + ", UnitFactory";
}

TowerFactory::TowerPrototype::TowerPrototype(sf::RenderWindow & window, string & tower_type, json & configs) {
	if (tower_type == "WatchTower")
		tower_ptr_ = make_shared<WatchTower>(WatchTower(window, configs));
}

shared_ptr<Tower> TowerFactory::TowerPrototype::Clone() {
	return tower_ptr_->Clone();
}
