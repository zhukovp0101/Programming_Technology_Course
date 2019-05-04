#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H


#include "Scene.h"
#include "BaseIncludes.h"


class Level: public Scene {
public:
	Level() = delete;
	explicit Level(sf::RenderWindow & window, const string & map_name, const string & map_resources);
	virtual ~Level() = default;

	void Draw() override;

	pair<size_t, size_t> GetSize() const;

	void Set(const string & map_name, const string & map_resources);

	virtual string GetInfo() const override;

private:
	class Map_: public IDrawingObject {
	public:
		explicit Map_ (sf::RenderWindow & window);
		void Set(const string & map_name, const string & map_resources);

		void Draw() override;

		pair<size_t, size_t> GetSize() const;

		virtual string GetInfo() const override;

	private:
		vector<bool> available_textures_;
		vector<vector<int>> state_;
		vector<sf::Texture> textures_;
		sf::Sprite sprite_;

		size_t height_ = 0;
		size_t width_ = 0;
		size_t tile_height_ = 0;
		size_t tile_width_ = 0;

		const int max_texture_number_ = 100;
		const int max_width_ = 100;
		const int max_height_ = 100;
	};

	Map_ map_;
};




class LevelFactory: public SceneFactory {
public:
	LevelFactory() = default;

	shared_ptr<Scene> Create(sf::RenderWindow &window, const string &map_name, const string &map_resources);

	virtual string GetInfo() const override;
};


#endif //GAME_LEVEL_H
