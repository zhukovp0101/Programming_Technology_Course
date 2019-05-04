#ifndef GAME_SCENE_H
#define GAME_SCENE_H


#include "IObject.h"
#include "BaseIncludes.h"


class Scene: public IDrawingObject {
public:
	explicit Scene(sf::RenderWindow & window);
	virtual ~Scene() = default;
	virtual void Draw() override = 0;
	void SetBackGround(string resource);
	const sf::Sprite & GetBackGround();

	virtual string GetInfo() const override;
private:
	sf::Sprite background_;
};




class SceneFactory: public IObject {
public:
	SceneFactory() = default;

	virtual ~SceneFactory() = default;

	virtual string GetInfo() const override;
};


#endif //GAME_SCENE_H
