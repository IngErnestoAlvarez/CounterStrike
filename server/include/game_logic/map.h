#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "cell.h"

class Game;
class World;

class Map {
private:
    World& world;
    std::vector<Cell> grid;
    int width;
    int height;
    std::string name;
    int starting_x_terrorists;
    int starting_y_terrorists;
    int starting_x_counterterrorists;
    int starting_y_counterterrorists;

public:
    Map(Game& game, const std::string& map_filepath);
    bool canBeAccesed(int x, int y);
    int getWeaponAt(int x, int y);
    const std::string& getName() const;
    int getWidth() const;
    int getHeight() const;
    Cell& getStartingCellTerrorists();
    Cell& getStartingCellCounterterrorists();
    std::vector<Cell>::iterator begin();
    std::vector<Cell>::iterator end();
    Cell& getCellAt(int x, int y);
    Cell& getCell(float x, float y);
};

#endif
