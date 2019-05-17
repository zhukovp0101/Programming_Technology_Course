#ifndef GAME_BASETESTINCLUDES_H
#define GAME_BASETESTINCLUDES_H

#include "gtest/gtest.h"
#include "BaseIncludes.h"

#ifdef DEBUG
#include "Unit.h"
#include "Parser.h"
#include "Scene.h"
#include "IMenu.h"
#include "Level/Level.h"
#include "IObject.h"
#include "ILivingObject.h"
#include "IEventObject.h"
#include "Factories/ItemFactory.h"
#include "IMenuItem.h"
#include "Button.h"
#include "Castle.h"
#include "IBuilding.h"

const string normal_resources = "Tests/Resources/Normal/";


class Test: public ::testing::Test {
public:
	Test(): app(sf::VideoMode(500, 500), "Tower Defense!") {
		app.setFramerateLimit(60);
	};
protected:
	static void SetUpTestSuite() {}
	vector<shared_ptr<Scene>> levels;
	vector<shared_ptr<Unit>> units;
	vector<shared_ptr<Scene>> menus;
	LevelFactory level_factory;
	UnitFactory unit_factory;
	MenuFactory menu_factory;
	sf::RenderWindow app;
};

class FinalTest: public ::testing::Test {
protected:
	void SetUp() {}
};

#endif
#endif //GAME_BASETESTINCLUDES_H
