#include "game_logic/weapons/ak47.h"
#include "types.h"

AK47::AK47(Game& game, Player& player)
           : Weapon("ak47", AK47_TYPE, game, player) {}

void AK47::use() {
    for (int i = 0; i < 3; i++) {
        this->createBullet();
    }
}
