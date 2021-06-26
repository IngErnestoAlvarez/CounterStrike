#ifndef AK47_H
#define AK47_H

#include "weapon.h"

class Game;
class Player;

class AK47 : public Weapon {
public:
    AK47(Game& game, Player& player);
    void use() override;
};

#endif
