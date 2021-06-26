#ifndef AWP_H
#define AWP_H

#include "weapon.h"

class Game;
class Body;

class AWP : public Weapon {
public:
    AWP(Game& game, Body& player);
    void use() override;
};

#endif
