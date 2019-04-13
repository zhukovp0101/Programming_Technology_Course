#include "BaseTestIncludes.h"

TEST_F(Test, CheckLevel)
{
	for (int i = 1; i < 11; ++i) {
		ASSERT_NO_THROW(levels.push_back(level_factory.Create(app, normal_resources + "Scenes/Levels/Maps/" + to_string(i) + "/map.txt")));
		EXPECT_FALSE(level_factory.Error());
		for (int j = 0; j < 10; ++j) {
			app.clear();
			levels[i - 1]->Draw();
			app.display();
		}
	}
	for (auto & level: levels)
		std::cout << level->GetInfo() << ", id: " + to_string(level->GetId()) << endl;
}

TEST_F(Test, CheckUnit)
{
	for (int i = 1; i < 2; ++i) {
		ASSERT_NO_THROW(unit_factory.Set(app, normal_resources + "Units/" + to_string(i) + "/Configs_.txt"));
		for (int j = 1; j < 11; ++j) {
			ASSERT_NO_THROW(units.push_back(unit_factory.Create(std::make_pair("Skeleton", "s1"))));
			ASSERT_NO_THROW(units.push_back(unit_factory.Create(std::make_pair("Witch", "w2"))));
		}
		EXPECT_FALSE(unit_factory.Error());
		for (auto & unit: units) {
			std::cout << unit->GetInfo() << ", id: " + to_string(unit->GetId()) << endl;
		}
	}
}

TEST_F(Test, CheckMenu) {
	for (int i = 1; i < 3; ++i) {
		ASSERT_NO_THROW(menus.push_back(menu_factory.Create(app, normal_resources + "Scenes/Menu/" + to_string(i) + "/menu.txt")));
		EXPECT_FALSE(level_factory.Error());
		for (int j = 0; j < 20; ++j) {
			app.clear();
			menus[i - 1]->Draw();
			app.display();
		}
	}
	for (auto & menu: menus)
		std::cout << menu->GetInfo() << ", id: " + to_string(menu->GetId()) << endl;
}

TEST_F(FinalTest, CheckMemory) {
	ASSERT_EQ(IObject::GetCount(), 0);
}

