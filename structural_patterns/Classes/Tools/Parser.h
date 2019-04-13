#ifndef GAME_PARSER_H
#define GAME_PARSER_H


#include "IObject.h"
#include "BaseIncludes.h"

#include "nlohmann/json.hpp"
using namespace nlohmann;


class Parser: public IObject {
public:
	Parser() = default;
	Parser(const Parser &) = delete;
	Parser & operator = (const Parser &) = delete;
	map<string, json> operator () (const string & filename);
	static map<string, json> File_To_Map(const string & filename) {
		ifstream file(filename);
		return json::parse(file);
	}
	static json File_To_Json(const string & filename) {
		ifstream file(filename);
		return json::parse(file);
	}
	static map<string, json> Json_To_Map(const json & source) {
		return source;
	}
	static int To_Int(const string & str);

	string GetInfo() const override;
};


#endif //GAME_PARSER_H
