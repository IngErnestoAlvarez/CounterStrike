#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Cell;
class World;

class Map {
private:
    World* world;
    std::vector<Cell*> grid;
    int width;
    int height;
    std::string name;

public:
    Map(World* world, const std::string& map_filepath);
    bool canBeAccesed(int x, int y);
    int getWeaponAt(int x, int y);
    const std::string& getName();
    Cell* getCellAt(int x, int y);


    int getWidth() const;
    int getHeight() const;
};

#endif
