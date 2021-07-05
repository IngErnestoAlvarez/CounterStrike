#ifndef CELL_H
#define CELL_H

#include "types.h"

class Game;
class Body;

class Cell {
private:
    BodyType type;
    float world_x;
    float world_y;
    Body* body;

public:
    explicit Cell(Game& game, BodyType type, float world_x, float world_y);
    ~Cell();
    bool canBeAccesed();
    float getWorldX();
    float getWorldY();
    BodyType getBodyType();
};

#endif
