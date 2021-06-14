#include <unordered_map>
#include "yaml-cpp/yaml.h"
#include "map.h"
#include "cell.h"
typedef std::unordered_map<std::string, std::string> MapObject;

Map::Map(const std::string& map_filepath) {
    YAML::Node map_object = YAML::LoadFile(map_filepath);
    std::vector<int> map_grid = map_object["grid"].as<std::vector<int>>();

    for (int cell : map_grid) {
        this->grid.push_back(new Cell(cell == 0));
    }

    this->name = map_object["name"].as<std::string>();
    this->width = std::stoi(map_object["width"].as<std::string>());
    this->height = std::stoi(map_object["height"].as<std::string>());
}

bool Map::canBeAccesed(int x, int y) {
    return this->getCellAt(x, y)->canBeAccesed();
}

const std::string& Map::getName() {
    return this->name;
}

Cell* Map::getCellAt(int x, int y) {
    return this->grid[this->height * y + x];
}

int Map::getWeaponAt(int x, int y) {
    return 1;
}

int Map::getWidth() const {
    return this->width;
}

int Map::getHeight() const {
    return this->height;
}
