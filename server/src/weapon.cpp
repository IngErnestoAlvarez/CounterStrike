#include "../include/weapon.h"
#include "../include/player.h"
#include "../include/configuration.h"

Weapon::Weapon(const std::string& name,
               const Configuration& config)
             : name(name),
               precision(config.getWeaponConfigValue(name, "precision")),
               damage(config.getWeaponConfigValue(name, "damage")),
               range(config.getWeaponConfigValue(name, "range")) {}

Weapon::~Weapon() {}
