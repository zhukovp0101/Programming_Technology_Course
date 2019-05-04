#include "Level.h"


Level::Level(sf::RenderWindow & window, const string & map_name, const string & map_resources): Scene(window), map_(window) {
	Set(map_name, map_resources);
}
void Level::Draw() {
	GetWindow().draw(GetBackGround());
	map_.Draw();
}

pair<size_t, size_t> Level::GetSize() const{
	return map_.GetSize();
}

void Level::Set(const string & map_name, const string & map_resources) {
	map_.Set(map_name, map_resources);
	if (map_.Error())
		SetError(map_.GetLastError());
}

string Level::GetInfo() const {
	return Scene::GetInfo() + ", Level";
}


Level::Map_::Map_ (sf::RenderWindow & window): IDrawingObject(window) {};

void Level::Map_::Set(const string & map_name, const string & map_resources) {
	ifstream map_file(map_name);
	if (!map_file.good()) {
		SetError("Cannot open file with card, file: " + map_name);
		return;
	}
	map_file >> height_ >> width_ >> tile_height_ >> tile_width_;
	if (map_file.fail()) {
		SetError("An error occurred while reading the card, file: " + map_name);
	}
	if (height_ > max_height_) {
		SetError("Maximum card height exceeded, max = " + to_string(max_height_));
		height_ = max_height_;
	}
	if (width_ > max_width_) {
		SetError("Maximum card width exceeded, max = " + to_string(max_width_));
		width_ = max_width_;
	}
	state_.resize(height_, vector<int>(width_, 0));
	int textures_current_max_number = 0;
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			map_file >> state_[i][j];
			if (state_[i][j] < 0) {
				SetError("An error occurred while reading the card, file: " + map_name);
				state_[i][j] = 0;
			}
			if (textures_current_max_number < state_[i][j])
				if (state_[i][j] <= max_texture_number_) {
					textures_current_max_number = state_[i][j];
				}
				else {
					state_[i][j] = 0;
					SetError("Maximum number of different textures exceeded, max = " + to_string(max_texture_number_));
				}
		}
	}
	map_file.close();

	available_textures_.resize(textures_current_max_number + 1, false);
	textures_.resize(textures_current_max_number + 1);
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			if (state_[i][j] != 0)
				if (!available_textures_[state_[i][j]]) {
						textures_[state_[i][j]].loadFromFile(map_resources + to_string(state_[i][j]) + ".png");
					available_textures_[state_[i][j]] = true;
				}
		}
	}
}

void Level::Map_::Draw() {
	for (size_t i = 0; i < height_; ++i) {
		for (size_t j = 0; j < width_; ++j) {
			if (state_[i][j] != 0) {
				sprite_.setTexture(textures_[state_[i][j]]);
				sprite_.setPosition(j * tile_width_, i * tile_height_);
				GetWindow().draw(sprite_);
			}
		}
	}
}

pair<size_t, size_t> Level::Map_::GetSize() const {
	return make_pair(width_ * tile_width_, height_ * tile_height_);
}

string Level::Map_::GetInfo() const {
	return IDrawingObject::GetInfo() + ", multimap";
}


shared_ptr<Scene> LevelFactory::Create(sf::RenderWindow & window, const string & map_name, const string & map_resources) {
	shared_ptr<Level> res = make_shared<Level>(window, map_name, map_resources);
	if (res->Error())
		SetError(res->GetLastError());
	return res;
}

string LevelFactory::GetInfo() const {
	return SceneFactory::GetInfo() + ", LevelFactory";
}
