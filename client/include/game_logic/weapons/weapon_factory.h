#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>

class Game;
class Weapon;

class WeaponFactory {
public:
    static Weapon* create(Game& game, const std::string& weapon_name);
};

#endif
