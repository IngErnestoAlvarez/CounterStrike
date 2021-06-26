#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

class b2World;
class Body;
class ContactListener;

class World {
   private:
    b2World *b2_world;
    std::vector<Body *> bodies;
    ContactListener* contact_listener;

    friend class Body;

   public:
    World();
    ~World();
    Body *createBody(float x, float y, float velocity);
    void step();
    std::vector<Body *> &getBodies();
};

#endif
