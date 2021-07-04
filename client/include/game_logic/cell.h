#ifndef CELL_H
#define CELL_H

class Body;

class Cell {
private:
    Body* body;
    float world_x;
    float world_y;

public:
    explicit Cell(Body* body, float world_x, float world_y);
    ~Cell();
    bool canBeAccesed();
    float getWorldX();
    float getWorldY();
    Body* getBody();
};

#endif
