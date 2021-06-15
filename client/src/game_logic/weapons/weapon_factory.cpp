#include "game_logic/weapons/weapon_factory.h"

#include "configuration.h"
#include "game_logic/game.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/weapon.h"

Weapon *WeaponFactory::create(Game &game, int weapon_id) {
    const Configuration &config = game.getConfig();
    switch (weapon_id) {
        case 1:
            return new Knife(config);
        case 2:
            return new Glock(config);
        default:
            throw new std::exception();
    }
}
