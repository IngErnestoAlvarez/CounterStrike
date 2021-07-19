#include <unordered_map>
#include "yaml-cpp/yaml.h"

#include "game_logic/block.h"
#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/world.h"
#include "types.h"

#define CELL_SIZE 32

Map::Map(Game& game, const std::string &map_filepath) : world(game.getWorld()) {
    YAML::Node map_object = YAML::LoadFile(map_filepath);
    std::vector<int> map_grid = map_object["grid"].as<std::vector<int>>();

    this->name = map_object["name"].as<std::string>();
    this->width = map_object["width"].as<int>();
    this->height = map_object["height"].as<int>();
    this->starting_x_terrorists = map_object["starting_x_terrorists"].as<int>();
    this->starting_y_terrorists = map_object["starting_y_terrorists"].as<int>();
    this->starting_x_counterterrorists = map_object["starting_x_counterterrorists"].as<int>();
    this->starting_y_counterterrorists = map_object["starting_y_counterterrorists"].as<int>();

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            BodyType cell_type = BodyType(map_grid[this->height * j + i]);
            float x = i * CELL_SIZE + CELL_SIZE / 2;
            float y = j * CELL_SIZE + CELL_SIZE / 2;
            this->grid.push_back(std::move(Cell(game, cell_type, x, y)));
        }
    }
}

bool Map::canBeAccesed(int x, int y) {
    return this->getCellAt(x, y).canBeAccesed();
}

const std::string &Map::getName() const { return this->name; }

Cell &Map::getCellAt(int x, int y) { return this->grid[this->height * y + x]; }

Cell& Map::getCellAt(float x, float y) {
    int i = (x - CELL_SIZE / 2) / CELL_SIZE;
    int j = (y - CELL_SIZE / 2) / CELL_SIZE;
    return this->getCellAt(i, j);
}

int Map::getWeaponAt(int x, int y) { return 1; }

int Map::getWidth() const { return this->width; }

int Map::getHeight() const { return this->height; }

Cell& Map::getStartingCellTerrorists() {
    return this->getCellAt(this->starting_x_terrorists,
                           this->starting_y_terrorists);
}

Cell& Map::getStartingCellCounterterrorists() {
    return this->getCellAt(this->starting_x_counterterrorists,
                           this->starting_y_counterterrorists);
}

std::vector<Cell>::iterator Map::begin() { return this->grid.begin(); }

std::vector<Cell>::iterator Map::end() { return this->grid.end(); }
