#include "Scene.h"


Scene::Scene(sf::RenderWindow & window) : IDrawingObject(window) {}

void Scene::SetBackGround(string resource) {
	background_texture_.loadFromFile(resource);
	background_.setTexture(background_texture_);
}

void Scene::Deactivate() {
	active_now_ = false;
}

void Scene::Activate() {
	active_now_ = true;
}

bool Scene::IsActiveNow() {
	return active_now_;
}

const sf::Sprite & Scene::GetBackGround() {
	return background_;
}

string Scene::GetInfo() const {
	return IDrawingObject::GetInfo() + ", Scene";
}

sf::Vector2u Scene::GetSize() const {
	return GetWindow().getSize();
}
