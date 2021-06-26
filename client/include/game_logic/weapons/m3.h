#ifndef M3_H
#define M3_H

#include "weapon.h"

class Game;
class Body;

class M3 : public Weapon {
public:
    M3(Game& game, Body& player);
    void use() override;
};

#endif
