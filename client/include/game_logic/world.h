#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

class b2World;
class Body;

class World {
   private:
    b2World *b2_world;
    std::vector<Body *> bodies;

    friend class Body;

   public:
    World();
    ~World();
    Body *createBody(float x, float y, float velocity);
    void step();
    std::vector<Body *> &getBodies();
};

#endif
