#include "game_logic/cell.h"
#include "game_logic/body.h"

Cell::Cell(Body* body, float world_x, float world_y)
	: body(body), world_x(world_x), world_y(world_y) {}

Cell::~Cell() {}

bool Cell::canBeAccesed() { return this->body == nullptr; }

float Cell::getWorldX() { return this->world_x; }

float Cell::getWorldY() { return this->world_y; }

Body* Cell::getBody() {
	return this->body;
}
