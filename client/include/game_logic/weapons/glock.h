#ifndef GLOCK_H
#define GLOCK_H

#include "weapon.h"

class Game;
class Body;

class Glock : public Weapon {
public:
    Glock(Game& game, Body& player);
    void use() override;
};

#endif
