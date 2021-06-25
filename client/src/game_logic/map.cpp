#include <unordered_map>
#include "game_logic/map.h"
#include "game_logic/world.h"
#include "yaml-cpp/yaml.h"

#define CELL_SIZE 30

Map::Map(World& world, const std::string &map_filepath) : world(world) {
    YAML::Node map_object = YAML::LoadFile(map_filepath);
    std::vector<int> map_grid = map_object["grid"].as<std::vector<int>>();

    this->name = map_object["name"].as<std::string>();
    this->width = std::stoi(map_object["width"].as<std::string>());
    this->height = std::stoi(map_object["height"].as<std::string>());

    int cell_type;
    float x;
    float y;

    for (int i = 0; i < this->width; i++) {
    	for (int j = 0; j < this->height; j++) {
    		cell_type = map_grid[this->height * j + i];
    		x = i * CELL_SIZE + CELL_SIZE / 2;
			y = j * CELL_SIZE + CELL_SIZE / 2;

    		if (cell_type != 0)
    			this->world.createBody(x, y, 0);
    		this->grid.push_back(Cell(cell_type == 0, x, y));
    	}
    }
}

bool Map::canBeAccesed(int x, int y) {
    return this->getCellAt(x, y).canBeAccesed();
}

const std::string &Map::getName() const { return this->name; }

Cell& Map::getCellAt(int x, int y) { return this->grid[this->height * y + x]; }

int Map::getWeaponAt(int x, int y) { return 1; }

int Map::getWidth() const { return this->width; }

int Map::getHeight() const { return this->height; }

std::vector<Cell>::iterator Map::begin() {
    return this->grid.begin();
}

std::vector<Cell>::iterator Map::end() {
    return this->grid.end();
}
