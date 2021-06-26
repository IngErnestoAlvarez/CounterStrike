#ifndef GLOCK_H
#define GLOCK_H

#include "weapon.h"

class Game;
class Player;

class Glock : public Weapon {
public:
    Glock(Game& game, Player& player);
    void use() override;
};

#endif
