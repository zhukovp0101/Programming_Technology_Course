#include "Scene.h"


Scene::Scene(sf::RenderWindow & window): IDrawingObject(window) {}

void Scene::SetBackGround(string resource) {
	sf::Texture t;
	t.loadFromFile(resource);
	background_.setTexture(t);
}

const sf::Sprite & Scene::GetBackGround() {
	return background_;
}

string Scene::GetInfo() const {
	return IDrawingObject::GetInfo() + ", Scene";
};

string SceneFactory::GetInfo() const {
	return IObject::GetInfo() + ", SceneFactory";
}
