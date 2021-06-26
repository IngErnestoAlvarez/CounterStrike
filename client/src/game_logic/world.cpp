#include <Box2D/Box2D.h>
#include "game_logic/world.h"
#include "game_logic/body.h"
#include "game_logic/cell.h"
#include "game_logic/map.h"
#include "game_logic/contact_listener.h"

#define CELL_SIZE 30

World::World()
    : b2_world(new b2World(b2Vec2(0, 0))),
      contact_listener(new ContactListener()) {
    this->b2_world->SetContactListener(this->contact_listener);
}

World::~World() {
    for (Body *body : this->bodies) {
        if (body != nullptr) {
            // delete body;
        }
    }

    delete this->b2_world;
    delete this->contact_listener;
}

Body *World::createBody(float x, float y, float velocity) {
    Body *body = new Body(*this, x, y, velocity);
    this->bodies.push_back(body);
    return body;
}

void World::step() {
    // revisar estos valores
    this->b2_world->Step(2000, 8, 3);
}

std::vector<Body *> &World::getBodies() { return this->bodies; }
