#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

class Game;
class Weapon;

class WeaponFactory {
public:
    static Weapon* create(Game& game, int weapon_id);
};

#endif
