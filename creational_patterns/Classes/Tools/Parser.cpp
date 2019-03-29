#include "Parser.h"


multimap<string, vector<string>> Parser::operator ()(const string & filename) {
	multimap<string, vector<string>> result;
	fstream file(filename);
	string input;
	if (!file.good()) {
		SetError("An error occurred while trying to open the file " + filename);
		return result;
	}
	while (getline(file, input)) {
		size_t index = input.find(' ', 0);
		if (index == -1) {
			SetError("Input data format does not match required: line " + input + " contains less than 2 words, file: " + filename);
			continue;
		}
		string key = input.substr(0, index);
		std::pair<string, vector<string>> item(key, {});
		while (input.find(' ', index + 1) != -1) {
			item.second.emplace_back(input.substr(index + 1, input.find(' ', index + 1) - index - 1));
			index = input.find(' ', index + 1);
		}
		if (input.substr(index + 1, input.size() - index - 1).rfind("\r") != -1)
			item.second.emplace_back(input.substr(index + 1, input.size() - index - 2));
		else
			item.second.emplace_back(input.substr(index + 1, input.size() - index - 1));
		result.emplace(item);
	}
	file.close();
	return result;
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



