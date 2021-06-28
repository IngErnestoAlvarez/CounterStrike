#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "body.h"

class Weapon;
class Game;

class Player : public Body {
private:
    Weapon* default_melee_weapon;
    Weapon* default_range_weapon;
    Weapon* primary_weapon;
    Weapon* equipped_weapon;

public:
    Player(Game& game, float x, float y);
    void addWeaponToInventory(Weapon* weapon);
    Weapon* getEquippedWeapon();
};

#endif
