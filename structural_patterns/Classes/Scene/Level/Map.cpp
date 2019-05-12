#include "Map.h"

Map::Map(sf::RenderWindow & window) : IDrawingObject(window) {
}

void Map::Set(const json & configs) {
	tile_width_ = configs["tilewidth"];
	tile_height_ = configs["tileheight"];
	for (auto & tileset_config: configs["tilesets"]) {
		TileSet_ tileset;
		tileset.tile_height_ = tileset_config["tileheight"];
		tileset.tile_width_ = tileset_config["tilewidth"];
		tileset.tiles_count_ = tileset_config["tilecount"];
		tileset.texture_.loadFromFile(string(configs["Resources"]) + string(tileset_config["image"]));
		tileset.width_ = tileset.texture_.getSize().x / tileset.tile_width_;
		tileset.height_ = tileset.texture_.getSize().y / tileset.tile_height_;
		tilesets_.push_back(tileset);
	}

	for (auto & layer_config: configs["layers"]) {
		if (layer_config["name"] == "Land") {
			width_ = layer_config["width"];
			height_ = layer_config["height"];
			land_.resize(height_);
			vector<int> data = layer_config["data"];
			for (int h = 0; h < height_; ++h) {
				land_[h].resize(width_);
				for (int w = 0; w < width_; ++w) {
					Tile_ t;
					t.position_ = Get_TextureNumber_And_Position_(data[h * width_ + w]).second;
					t.tileset_number_ = Get_TextureNumber_And_Position_(data[h * width_ + w]).first;
					land_[h][w] = t;
				}
			}
		}
	}
}

void Map::Draw() { //TODO: оптимизировать для больших карт;
	int current_tileset_number = -1;
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			if (land_[i][j].tileset_number_ != -1) {
				if (land_[i][j].tileset_number_ != current_tileset_number) {
					current_tileset_number = land_[i][j].tileset_number_;
					sprite_.setTexture(tilesets_[current_tileset_number].texture_);
				}
				sprite_.setTextureRect(sf::IntRect(land_[i][j].position_.x, land_[i][j].position_.y,
				                                   tilesets_[current_tileset_number].tile_width_,
				                                   tilesets_[current_tileset_number].tile_height_));
				sprite_.setPosition(j * tile_width_, i * tile_height_);
				GetWindow().draw(sprite_);
			}
		}
	}
}

sf::Vector2u Map::GetSize() const {
	return sf::Vector2u(width_ * tile_width_, height_ * tile_height_);
}

string Map::GetInfo() const {
	return IDrawingObject::GetInfo() + ", multimap";
}

pair<int, sf::Vector2u> Map::Get_TextureNumber_And_Position_(int tile_number) { // Помнить, что нумерация с 1;
	if (tile_number != 0) {
		for (int i = 0, count = 0; i < tilesets_.size(); ++i, count += tilesets_[i].tiles_count_) {
			if (count + tilesets_[i].tiles_count_ >= tile_number) {
				return make_pair(i, sf::Vector2u((tile_number - count - 1) % tilesets_[i].width_ * tilesets_[i].tile_width_,
				                                 (tile_number - count - 1) / tilesets_[i].width_ * tilesets_[i].tile_height_));
			}
		}
	}
	return make_pair(-1, sf::Vector2u(0, 0));
}
