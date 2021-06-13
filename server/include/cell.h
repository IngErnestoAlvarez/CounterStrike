#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool accesible;
    int type_id;

public:
    explicit Cell(bool accesible);
    ~Cell();
    bool canBeAccesed();
};

#endif
