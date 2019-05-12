#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H


#include "Scene.h"
#include "IEventObject.h"
#include "Map.h"
#include "Parser.h"
#include "BaseIncludes.h"
#include "TowerFactory.h"


class Level: public Scene, public IEventObject, public IUpdateObject {
public:
	Level() = delete;

	explicit Level(sf::RenderWindow & window, const string & filename);;

	virtual ~Level() = default;

	void Draw() override;;

	sf::Vector2u GetSize() const override;;

	void Set(const string & filename);;

	virtual string GetInfo() const override;;

	void Activate() override;

	void Deactivate() override;

	void Update() override;

	void AddTower(const string &tower_type, int x, int y);

private:
	class Scroll: public Command<sf::Event> {
	public:
		explicit Scroll(Level * level);;
		const void operator ()(const sf::Event & event) override;
	private:
		Level * level_;
	};
	class KeyPressed: public Command<sf::Event> {
	public:
		explicit KeyPressed(Level * level);;
		const void operator ()(const sf::Event & event) override;;
	private:
		Level * level_;
	};
	class KeyReleased: public Command<sf::Event> {
	public:
		explicit KeyReleased(Level * level);;
		const void operator ()(const sf::Event & event) override;
	private:
		Level * level_;
	};

	class MouseMoved: public Command<sf::Event> {
	public:
		explicit MouseMoved(Level * level);;
		const void operator ()(const sf::Event & event) override;
	private:
		Level * level_;
	};

	class MouseButtonPressed: public Command<sf::Event> {
	public:
		explicit MouseButtonPressed(Level * level);;
		const void operator ()(const sf::Event & event) override;
	private:
		Level * level_;
	};

	void SmartMove();
	Map map_;
	TowerFactory tower_factory_;
	vector<shared_ptr<Tower>> towers_ptrs_;
	sf::View view_;
	int moving_x_ = 0;
	int moving_y_ = 0;
	sf::Vector2f min_speed_ = {40, 40};
	sf::Vector2f speed_ = min_speed_;
	bool moving_now_ = false;

};


#endif //GAME_LEVEL_H
