#ifndef KNIFE_H
#define KNIFE_H

#include "weapon.h"

class Game;
class Body;

class Knife : public Weapon {
public:
    Knife(Game& game, Body& player);
    void use() override;
};

#endif
