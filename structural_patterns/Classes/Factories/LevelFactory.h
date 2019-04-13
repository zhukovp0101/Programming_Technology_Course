#ifndef GAME_LEVELFACTORY_H
#define GAME_LEVELFACTORY_H

#include "SceneFactory.h"
#include "Level/Level.h"
#include "BaseIncludes.h"

class LevelFactory: public SceneFactory {
public:
	LevelFactory() = default;

	shared_ptr<Scene> Create(sf::RenderWindow &window, const string &filename) {
		shared_ptr<Level> res = make_shared<Level>(window, filename);
		if (res->Error())
			SetError(res->GetLastError());
		return res;
	};

	virtual string GetInfo() const override {
		return SceneFactory::GetInfo() + ", LevelFactory";
	};
};


#endif //GAME_LEVELFACTORY_H
