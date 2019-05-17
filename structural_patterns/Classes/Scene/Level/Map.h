#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "IObject.h"
#include "BaseIncludes.h"
#include "Parser.h"

class Map : public IDrawingObject {
public:
	explicit Map(sf::RenderWindow & window);;

	void Set(const json & configs);;

	void Draw() override;;

	sf::Vector2u GetSize() const;;

	string GetInfo() const override;;

private:
	struct TileSet_ {
		sf::Texture texture_;
		int tiles_count_ = 0;
		int tile_width_ = 0;
		int tile_height_ = 0;
		int width_ = 0; // Помнить, что это кол-во тайлов, а не пикселей;
		int height_ = 0;
	};

	struct Tile_ {
		int tileset_number_ = 0;
		sf::Vector2u position_ = {0, 0};
	};

	pair<int, sf::Vector2u> Get_TextureNumber_And_Position_(int tile_number);;

	vector<vector<Tile_>> land_;
	vector<TileSet_> tilesets_;
	sf::Sprite sprite_;

	size_t height_ = 0;
	size_t width_ = 0;
	size_t tile_height_ = 0;
	size_t tile_width_ = 0;

	const int max_texture_number_ = 100;
	const int max_width_ = 100;
	const int max_height_ = 100;
};


#endif //GAME_MAP_H
