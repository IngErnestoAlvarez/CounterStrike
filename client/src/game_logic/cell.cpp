#include "game_logic/cell.h"

Cell::Cell(bool accesible) : accesible(accesible) {}

Cell::~Cell() {}

bool Cell::canBeAccesed() { return this->accesible; }
