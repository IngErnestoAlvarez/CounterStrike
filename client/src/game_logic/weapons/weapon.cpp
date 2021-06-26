#include "game_logic/weapons/weapon.h"
#include "game_logic/player.h"
#include "game_logic/game.h"
#include "game_logic/configuration.h"

Weapon::Weapon(const std::string& name,
               Game& game,
               Body& player)
             : name(name),
               world(game.getWorld()),
               player(player) {
    Configuration& config = game.getConfig();
    this->damage = config.getWeaponConfigValue(weapon_name, "damage");
    this->precision = config.getWeaponConfigValue(weapon_name, "precision");
    this->range = config.getWeaponConfigValue(weapon_name, "range");
}

Weapon::~Weapon() {}
