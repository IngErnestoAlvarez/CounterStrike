#include <Box2D/Box2D.h>
#include "game_logic/world.h"
#include "game_logic/body.h"
#include "game_logic/cell.h"
#include "game_logic/map.h"
#include "game_logic/contact_listener.h"
#include "game_logic/block.h"
#include "game_logic/game.h"

#define CELL_SIZE 30

World::World(Game& game)
    : game(game),
      b2_world(new b2World(b2Vec2(0, 0))),
      contact_listener(new ContactListener()) {
    this->b2_world->SetContactListener(this->contact_listener);
}

World::~World() {
    for (Body *body : this->bodies) {
        if (body != nullptr) {
            body->destroy();
        }
    }

    delete this->b2_world;
    delete this->contact_listener;
}

// cambiar esto
Block *World::createBody(float x, float y) {
    return new Block(this->game, x, y);
}

void World::step() {
    for (Body* body : this->bodies) {
        body->update();
        if (body->toBeDestroyed()) {
            body->destroy();
        }
    }
    // revisar estos valores
    this->b2_world->Step(2000, 8, 3);
}

std::vector<Body *> &World::getBodies() { return this->bodies; }
