#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Cell;

class Map {
private:
    std::vector<Cell*> grid;
    int width;
    int height;
    std::string name;

public:
    Map(const std::string& map_filepath);
    bool canBeAccesed(int x, int y);
    int getWeaponAt(int x, int y);
    const std::string& getName();
    Cell* getCellAt(int x, int y);


    int getWidth() const;
    int getHeight() const;
};

#endif
