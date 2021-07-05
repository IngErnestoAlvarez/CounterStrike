#include "game_logic/weapons/ak47.h"

AK47::AK47(Game& game, Player& player)
           : Weapon("ak47", game, player) {}

void AK47::use() {
    for (int i = 0; i < 3; i++) {
        this->createBullet();
    }
}
