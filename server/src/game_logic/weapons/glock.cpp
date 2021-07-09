#include "game_logic/weapons/glock.h"

#include "configuration.h"
#include "game_logic/game.h"
#include "types.h"

Glock::Glock(Game& game, Player& player)
          : Weapon("glock", GLOCK_TYPE, game, player) {}

void Glock::use() {
    this->createBullet();
}
