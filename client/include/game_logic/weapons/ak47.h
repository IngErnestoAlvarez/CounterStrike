#ifndef AK47_H
#define AK47_H

#include "weapon.h"

class Game;
class Body;

class AK47 : public Weapon {
public:
    AK47(Game& game, Body& player);
    void use() override;
};

#endif
