#include "game_logic/world.h"
#include "game_logic/map.h"
#include "game_logic/cell.h"
#include "game_logic/body.h"
#include <Box2D/Box2D.h>

#define CELL_SIZE 30

World::World() : b2_world(new b2World(b2Vec2(0, 0))) {}

World::~World() {
    for (Body* body : this->bodies) {
        if (body != nullptr) {
            body->destroy();
        }
    }

    delete this->b2_world;
}

World::World(const std::string& map_filepath) : World() {
	Map map(map_filepath);

	int map_width = map.getWidth();
	int map_height = map.getHeight();
	Cell* cell;
	float x;
	float y;

	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			cell = map.getCellAt(i, j);
			if (!cell->canBeAccesed()) {
				x = i * CELL_SIZE + CELL_SIZE / 2;
				y = j * CELL_SIZE + CELL_SIZE / 2;
				new Body(this, x, y, 0);
			}
		}
	}
}

std::vector<Body*> World::getBodies() {
	return this->bodies;
}

void World::step() {
	// revisar estos valores
	this->b2_world->Step(2000, 8, 3);
}
