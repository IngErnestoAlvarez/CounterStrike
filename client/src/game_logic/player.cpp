#include "game_logic/player.h"

#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/glock.h"

#define INITIAL_PLAYER_ANGLE 0

Player::Player(Game& game, float x, float y)
    : Body(game.getWorld(),
           x, y,
           INITIAL_PLAYER_ANGLE,
           game.getConfig().getPlayerSpeed()),
      default_melee_weapon(new Knife(game, *this)),
      default_range_weapon(new Glock(game, *this)),
      primary_weapon(nullptr),
      equipped_weapon(default_range_weapon) {}

void Player::addWeaponToInventory(Weapon* weapon) {
    // terminar este metodo
    this->primary_weapon = weapon;
}

Weapon* Player::getEquippedWeapon() {
    return this->equipped_weapon;
}
