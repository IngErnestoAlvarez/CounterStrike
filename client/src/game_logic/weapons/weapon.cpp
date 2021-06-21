#include "game_logic/weapons/weapon.h"
#include "game_logic/player.h"

Weapon::Weapon(const std::string& name,
               float damage,
               float precision,
               float range)
             : name(name),
               damage(damage),
               precision(precision),
               range(range) {}

Weapon::~Weapon() {}
