#include "game_logic/weapons/awp.h"

AWP::AWP(Game& game, Player& player)
           : Weapon("awp", game, player) {}

void AWP::use() {
    this->createBullet();
}
