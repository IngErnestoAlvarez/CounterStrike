#include "game_logic/player.h"

#include "game_logic/game.h"
#include "game_logic/map.h"

Player::Player(World& world, Configuration& config, float x, float y)
    : Body(world, x, y, config.getPlayerSpeed()) {}

void Player::addWeaponToInventory(Weapon* weapon) {
    this->inventory.push_back(weapon);
}