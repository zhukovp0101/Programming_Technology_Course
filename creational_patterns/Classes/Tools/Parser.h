#ifndef GAME_PARSER_H
#define GAME_PARSER_H


#include "IObject.h"
#include "BaseIncludes.h"


class Parser: public IObject {
public:
	Parser() = default;
	Parser(const Parser &) = delete;
	Parser & operator = (const Parser &) = delete;
	multimap<string, vector<string>> operator () (const string & filename);
	int To_Int(const string & str);

	string GetInfo() const override;
};


#endif //GAME_PARSER_H
