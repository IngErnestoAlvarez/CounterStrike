#ifndef KNIFE_H
#define KNIFE_H

#include "weapon.h"

class Game;
class Player;

class Knife : public Weapon {
public:
    Knife(Game& game, Player& player);
    void use() override;
};

#endif
