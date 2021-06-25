#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "cell.h"
#include "world.h"

class Map {
private:
    World& world;
    std::vector<Cell> grid;
    int width;
    int height;
    std::string name;
    Cell& getCellAt(int x, int y);

public:
    Map(World& world, const std::string& map_filepath);
    bool canBeAccesed(int x, int y);
    int getWeaponAt(int x, int y);
    const std::string& getName() const;
    int getWidth() const;
    int getHeight() const;
    std::vector<Cell>::iterator begin();
    std::vector<Cell>::iterator end();
};

#endif
