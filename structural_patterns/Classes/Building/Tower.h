#ifndef GAME_TOWER_H
#define GAME_TOWER_H

#include "IMenu.h"
#include "MenuPage.h"
#include "Unit.h"
#include "IEventObject.h"
#include "ILivingObject.h"


class Tower: public IEventObject, public ILivingObject{
public:
	Tower(sf::RenderWindow & window, json & configs);

	Tower(const Tower & copy);

	virtual shared_ptr<Tower> Clone();

	void Draw() override;

	void SetPosition(int x, int y);

protected:
	class SelectionMenu: public IMenu {
	public:
		SelectionMenu(sf::RenderWindow & window, Tower * tower, const string & filename);;
		SelectionMenu(const SelectionMenu & copy, Tower * tower);
		Tower * tower_;
	private:
		string filename_;
	};

	class MouseMoved: public Command<sf::Event> {
	public:
		explicit MouseMoved(Tower * tower): tower_(tower) {};
		const void operator ()(const sf::Event & event) override {
			if (tower_->ContainsPoint(event.mouseMove.x, event.mouseMove.y))
				if (! tower_->active_selection_now_) {
					tower_->ActivateSelection();
				}
				else {}
			else
				tower_->DeactivateSelection();
		}
	private:
		Tower * tower_;
	};

	class MouseButtonPressed: public Command<sf::Event> {
	public:
		explicit MouseButtonPressed(Tower * tower);;
		const void operator ()(const sf::Event & event) override;
	private:
		Tower * tower_;
	};

	struct BulletConfigs {
	public:
		explicit BulletConfigs(json & configs);
		BulletConfigs() = default;
		shared_ptr<Command<Unit>> OnCollision;
		sf::Texture texture_;
		int damage = 0;
	};
	struct TowerConfigs {
		sf::Texture texture_;
		BulletConfigs bullet_configs_;
		int height = 0;
		int width = 0;
		int radius = 0;
		int rate_fire = 0; // один выстрел в rate_fire milliseconds;
		int max_health = 0;
	};

	void ActivateSelection();

	void DeactivateSelection();

	bool ContainsPoint(const int & x, const int & y);

	shared_ptr<vector<TowerConfigs>> improvements_configs_ptr_;
	shared_ptr<SelectionMenu> selection_menu_ptr_;
	int current_level_ = 0;
	sf::Sprite sprite_;
	bool active_selection_now_ = false;
};


class WatchTower: public Tower {
public:
	WatchTower(sf::RenderWindow & window, json & configs);;
};

#endif //GAME_TOWER_H
