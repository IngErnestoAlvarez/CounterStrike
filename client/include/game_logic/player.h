#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "body.h"

class Weapon;
class Game;
class Configuration;

class Player : public Body {
private:
    std::vector<Weapon*> inventory;

public:
    Player(World& world, Configuration& config, float x, float y);
    void addWeaponToInventory(Weapon* weapon);
};

#endif
