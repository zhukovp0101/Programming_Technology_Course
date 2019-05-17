#include "Parser.h"


map<string, json> Parser::operator ()(const string & filename) {
	ifstream file(filename);
	return json::parse(file);
}

int Parser::To_Int(const string & str) {
	try {
		return stoi(str);
	}
	catch (...) {
		SetError("An error occurred while trying to convert a string " + str + " to int");
		return 0;
	}
}

string Parser::GetInfo() const {
	return IObject::GetInfo() + ", Parser";
}

map<string, json> Parser::File_To_Map(const string & filename) {
	ifstream file(filename);
	return json::parse(file);
}

json Parser::File_To_Json(const string & filename) {
	ifstream file(filename);
	return json::parse(file);
}

map<string, json> Parser::Json_To_Map(const json & source) {
	return source;
}



