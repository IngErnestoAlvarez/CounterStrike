#include "game_logic/cell.h"

Cell::Cell(bool accesible, float world_x, float world_y) : accesible(accesible), world_x(world_x), world_y(world_y) {}

Cell::~Cell() {}

bool Cell::canBeAccesed() { return this->accesible; }

float Cell::getWorldX() { return this->world_x; }

float Cell::getWorldY() { return this->world_y; }
