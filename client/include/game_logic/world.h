#ifndef WORLD_H
#define WORLD_H

#include <vector>

class b2World;
class Body;

class World {
private:
    b2World* b2_world;
    std::vector<Body*> bodies;

    friend class Body;

public:
    World();
    ~World();
};

#endif
