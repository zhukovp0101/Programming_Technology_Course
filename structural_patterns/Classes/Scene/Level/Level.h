#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H


#include "Scene.h"
#include "Map.h"
#include "Parser.h"
#include "BaseIncludes.h"


class Level: public Scene {
public:
	Level() = delete;

	explicit Level(sf::RenderWindow & window, const string & filename): Scene(window), map_(window) {
		Set(filename);
	};

	virtual ~Level() = default;

	void Draw() override {
		GetWindow().draw(GetBackGround());
		map_.Draw();
	};

	sf::Vector2u GetSize() const override {
		return map_.GetSize();
	};

	void Set(const string & filename) {
		map<string, json> configs = Parser::File_To_Json(filename);

		configs["Map"]["Resources"] = configs["Resources"];
		map_.Set(configs["Map"]);
		if (Map::Error())
			SetError(Map::GetLastError());
	};

	virtual string GetInfo() const override {
		return Scene::GetInfo() + ", Level";
	};

private:
	Map map_;
};


#endif //GAME_LEVEL_H
