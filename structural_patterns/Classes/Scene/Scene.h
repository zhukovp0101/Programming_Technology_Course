#ifndef GAME_SCENE_H
#define GAME_SCENE_H


#include "IObject.h"
#include "BaseIncludes.h"


class Scene: public IDrawingObject {
public:
	explicit Scene(sf::RenderWindow & window): IDrawingObject(window) {};
	virtual ~Scene() = default;
	virtual void Draw() override = 0;
	void SetBackGround(string resource) {
		background_texture_.loadFromFile(resource);
		background_.setTexture(background_texture_);
	};
	const sf::Sprite & GetBackGround() {
		return background_;
	};

	virtual string GetInfo() const override {
		return IDrawingObject::GetInfo() + ", Scene";
	};

	virtual sf::Vector2u GetSize() const = 0;
private:
	sf::Sprite background_;
	sf::Texture background_texture_;
};


#endif //GAME_SCENE_H
