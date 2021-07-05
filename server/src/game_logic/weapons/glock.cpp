#include "game_logic/weapons/glock.h"

#include "configuration.h"
#include "game_logic/game.h"

Glock::Glock(Game& game, Player& player)
          : Weapon("glock", game, player) {}

void Glock::use() {
    this->createBullet();
}
