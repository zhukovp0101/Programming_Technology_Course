#include "Unit.h"

Unit::Unit(sf::RenderWindow & window): ILivingObject(window) {

}

string Unit::GetInfo() const {
	return ILivingObject::GetInfo() + ", Unit";
}


Skeleton::Skeleton(sf::RenderWindow & window, string setting_name, string settings_resources): Unit(window) {

}

void Skeleton::Draw() {

}

shared_ptr<Unit> Skeleton::Clone() const {
	return shared_ptr<Unit>(new Skeleton(*this));
}

string Skeleton::GetInfo() const {
	return Unit::GetInfo() + ", Skeleton";
}


Witch::Witch(sf::RenderWindow & window, string setting_name, string settings_resources) : Unit(window) {

}

void Witch::Draw() {

}

shared_ptr<Unit> Witch::Clone() const {
	return shared_ptr<Unit>(new Witch(*this));
}

string Witch::GetInfo() const {
	return Unit::GetInfo() + ", Witch";
}


shared_ptr<Unit> UnitFactory::Create(pair<string, int> id) {
	if (prototypes_.find(id) != prototypes_.end())
		return prototypes_[id]->Clone();
	else {
		SetError("Attempt to create a unit with an unknown id: " + id.first + ' ' + to_string(id.second));
		return nullptr;
	}
}

void UnitFactory::Set(sf::RenderWindow & window, const string & filename, const string & settings_resources) {
	Parser parser;
	multimap<string, vector<string>> units_prototypes = parser(filename);
	if (parser.Error()) {
		SetError(parser.GetLastError());
	}
	string unit_type;
	int unit_number;
	string unit_filename;
	for (auto & prototype: units_prototypes) {
		unit_type = prototype.first;
		if (prototype.second.size() != 2) {
			SetError("Входной формат данных описания прототипа " + prototype.first + " не соответствует нужному, файл: " + filename);
		}
		unit_number = parser.To_Int(prototype.second[0]);
		if (parser.Error()) {
			SetError(parser.GetLastError());
			continue;
		}
		unit_filename = prototype.second[1];

		if (unit_type == "Skeleton")
			prototypes_.emplace(pair<string, int>("Skeleton", unit_number), shared_ptr<Unit>(new Skeleton(window, unit_filename, settings_resources)));
		if (unit_type == "Witch")
			prototypes_.emplace(pair<string, int>("Witch", unit_number), shared_ptr<Unit>(new Witch(window, unit_filename, settings_resources)));
	}
}

string UnitFactory::GetInfo() const {
	return IObject::GetInfo() + ", UnitFactory";
}
