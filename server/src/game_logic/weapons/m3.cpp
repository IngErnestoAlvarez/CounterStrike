#include "game_logic/weapons/m3.h"
#include "types.h"

M3::M3(Game& game, Player& player)
           : Weapon("m3", AK47_TYPE, game, player) {}

void M3::use() {
    this->createBullet(-15);
    this->createBullet();
    this->createBullet(15);
}
