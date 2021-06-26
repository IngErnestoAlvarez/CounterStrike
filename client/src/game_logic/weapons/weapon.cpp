#include "game_logic/weapons/weapon.h"
#include "game_logic/player.h"
#include "game_logic/world.h"
#include "game_logic/game.h"
#include "configuration.h"

Weapon::Weapon(const std::string& name,
               Game& game,
               Player& player)
             : name(name),
               game(game),
               world(game.getWorld()),
               player(player) {
    const Configuration& config = game.getConfig();
    this->damage = config.getWeaponConfigValue(name, "damage");
    this->precision = config.getWeaponConfigValue(name, "precision");
    this->range = config.getWeaponConfigValue(name, "range");
}

Weapon::~Weapon() {}
