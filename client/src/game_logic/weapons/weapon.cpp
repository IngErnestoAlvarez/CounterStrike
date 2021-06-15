#include "game_logic/weapons/weapon.h"

#include "configuration.h"
#include "game_logic/player.h"

Weapon::Weapon(const std::string &name, const Configuration &config)
    : name(name),
      precision(config.getWeaponConfigValue(name, "precision")),
      damage(config.getWeaponConfigValue(name, "damage")),
      range(config.getWeaponConfigValue(name, "range")) {}

Weapon::~Weapon() {}
