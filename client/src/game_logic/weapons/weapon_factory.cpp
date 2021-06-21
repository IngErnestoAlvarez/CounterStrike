#include "game_logic/weapons/weapon_factory.h"

#include "configuration.h"
#include "game_logic/game.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/weapon.h"

Weapon* WeaponFactory::create(Game& game, const std::string& weapon_name) {
    const Configuration &config = game.getConfig();

    float damage = config.getWeaponConfigValue(weapon_name, "damage");
    float precision = config.getWeaponConfigValue(weapon_name, "precision");
    float range = config.getWeaponConfigValue(weapon_name, "range");

    if (weapon_name == "knife") {
        return new Knife(damage, precision, range);
    }

    if (weapon_name == "glock") {
        return new Glock(damage, precision, range);
    }

    // terminar esto

    return nullptr;
}
