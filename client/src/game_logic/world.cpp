#include "game_logic/world.h"
#include "game_logic/body.h"
#include <Box2D/Box2D.h>

World::World() : b2_world(new b2World(b2Vec2(0, 0))) {}

World::~World() {
    for (Body* body : this->bodies) {
        if (body != nullptr) {
            body->destroy();
        }
    }

    delete this->b2_world;
}

void World::step() {
	// revisar estos valores
	this->b2_world->Step(2000, 8, 3);
}
