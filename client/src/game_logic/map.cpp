#include "game_logic/map.h"

#include <unordered_map>

#include "game_logic/world.h"
#include "game_logic/block.h"
#include "yaml-cpp/yaml.h"

#define CELL_SIZE 32

Map::Map(World &world, const std::string &map_filepath) : world(world) {
    YAML::Node map_object = YAML::LoadFile(map_filepath);
    std::vector<int> map_grid = map_object["grid"].as<std::vector<int>>();

    this->name = map_object["name"].as<std::string>();
    this->width = std::stoi(map_object["width"].as<std::string>());
    this->height = std::stoi(map_object["height"].as<std::string>());
    this->starting_x_terrorists = map_object["starting_x_terrorists"].as<int>();
    this->starting_y_terrorists = map_object["starting_y_terrorists"].as<int>();
    this->starting_x_antiterrorists = map_object["starting_x_antiterrorists"].as<int>();
    this->starting_y_antiterrorists = map_object["starting_y_antiterrorists"].as<int>();

    int cell_type;
    float x;
    float y;
    Body* body = nullptr;

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            cell_type = map_grid[this->height * j + i];
            x = i * CELL_SIZE + CELL_SIZE / 2;
            y = j * CELL_SIZE + CELL_SIZE / 2;

            if (cell_type != 0) {
                body = this->world.createBody(x, y);
            }
            this->grid.push_back(Cell(body, x, y));
            body = nullptr;
        }
    }
}

bool Map::canBeAccesed(int x, int y) {
    return this->getCellAt(x, y).canBeAccesed();
}

const std::string &Map::getName() const { return this->name; }

Cell &Map::getCellAt(int x, int y) { return this->grid[this->height * y + x]; }

int Map::getWeaponAt(int x, int y) { return 1; }

int Map::getWidth() const { return this->width; }

int Map::getHeight() const { return this->height; }

Cell& Map::getStartingCellTerrorists() {
    return this->getCellAt(this->starting_x_terrorists,
                           this->starting_y_terrorists);
}

Cell& Map::getStartingCellAntiterrorists() {
    return this->getCellAt(this->starting_x_antiterrorists,
                           this->starting_y_antiterrorists);
}

std::vector<Cell>::iterator Map::begin() { return this->grid.begin(); }

std::vector<Cell>::iterator Map::end() { return this->grid.end(); }
