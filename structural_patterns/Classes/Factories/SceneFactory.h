#ifndef GAME_SCENEFACTORY_H
#define GAME_SCENEFACTORY_H

#include "IObject.h"
#include "Scene.h"


class SceneFactory: public IObject {
public:
	SceneFactory() = default;

	virtual ~SceneFactory() = default;

	virtual shared_ptr<Scene> Create(sf::RenderWindow &window, const string &filename) = 0;

	virtual string GetInfo() const override {
		return IObject::GetInfo() + ", SceneFactory";
	}
};


#endif //GAME_SCENEFACTORY_H
