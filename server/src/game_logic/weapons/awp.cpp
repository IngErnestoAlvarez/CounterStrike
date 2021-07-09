#include "game_logic/weapons/awp.h"
#include "types.h"

AWP::AWP(Game& game, Player& player)
           : Weapon("awp", AK47_TYPE, game, player) {}

void AWP::use() {
    this->createBullet();
}
