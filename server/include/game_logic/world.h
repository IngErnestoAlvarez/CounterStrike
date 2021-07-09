#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

class b2World;
class Game;
class Body;
class Block;
class ContactListener;

class World {
   private:
    Game& game;
    b2World *b2_world;
    std::vector<Body *> bodies;
    ContactListener* contact_listener;

    friend class Body;

   public:
    World(Game& game);
    ~World();
    void step();
    std::vector<Body *> &getBodies();
};

#endif
