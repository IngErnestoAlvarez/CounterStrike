#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class World;
class Body;
class Configuration;

class Weapon {
private:
    std::string name;
    World& world;
    Body& player;
    float damage;
    float precision;
    float range;

public:
    Weapon(const std::string& name,
           Configuration& config,
           Body& player);
    virtual void use() = 0;
    ~Weapon();
};

#endif
