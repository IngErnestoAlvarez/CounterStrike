#ifndef AWP_H
#define AWP_H

#include "weapon.h"

class Game;
class Player;

class AWP : public Weapon {
public:
    AWP(Game& game, Player& player);
    void use() override;
};

#endif
