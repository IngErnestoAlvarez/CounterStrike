#include "game_logic/weapons/glock.h"

#include "configuration.h"
#include "game_logic/game.h"

Glock::Glock(Game& game, Player& player)
          : Weapon("glock", game, player) {}

void Glock::use() {
    // Bullet* bullet = new Bullet(this->game.getWorld(), this->player);
    // this->active_bullets.push_back(bullet);
    // bullet.move();
}
