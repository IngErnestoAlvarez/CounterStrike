#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>

class Weapon;
class Game;
class Body;

class WeaponFactory {
public:
    static Weapon* create(Game& game,
                          Body& player,
                          const std::string& weapon_name);
};

#endif
