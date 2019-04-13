#ifndef GAME_MENUFACTORY_H
#define GAME_MENUFACTORY_H


#include "SceneFactory.h"
#include "Menu.h"


class MenuFactory: public SceneFactory {
public:
	shared_ptr<Scene> Create(sf::RenderWindow &window, const string &filename) override {
		shared_ptr<Menu> res = make_shared<Menu>(window, filename);
		if (res->Error())
			SetError(res->GetLastError());
		return res;
	};
	string GetInfo() const override {
		return SceneFactory::GetInfo() + ", MenuFactory";
	};
};


#endif //GAME_MENUFACTORY_H
