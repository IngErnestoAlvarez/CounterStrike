#include "game_logic/weapons/m3.h"

M3::M3(Game& game, Player& player)
           : Weapon("m3", game, player) {}

void M3::use() {
    this->createBullet(-15);
    this->createBullet();
    this->createBullet(15);
}
