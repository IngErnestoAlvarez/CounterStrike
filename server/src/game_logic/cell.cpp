#include "game_logic/cell.h"
#include "game_logic/body.h"
#include "game_logic/block.h"
#include "game_logic/game.h"

Cell::Cell(Game& game, BodyType type, float world_x, float world_y)
	: type(type), world_x(world_x), world_y(world_y), body(nullptr) {
	if (type == WALL_TYPE) {
		this->body = new Block(game, world_x, world_y);
	}
}

Cell::~Cell() {
	// if (this->body != nullptr) {
	// 	delete this->body;
	// }
}

bool Cell::canBeAccesed() { return this->type == OFFICE_TYPE; }

float Cell::getWorldX() { return this->world_x; }

float Cell::getWorldY() { return this->world_y; }

BodyType Cell::getBodyType() {
	return this->type;
}
