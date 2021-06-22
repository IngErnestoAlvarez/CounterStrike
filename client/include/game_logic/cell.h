#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool accesible;
    int type_id;
    float world_x;
    float world_y;

public:
    explicit Cell(bool accesible, float world_x, float world_y);
    ~Cell();
    bool canBeAccesed();
    float getWorldX();
    float getWorldY();
};

#endif
