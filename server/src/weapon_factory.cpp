#include "../include/weapon_factory.h"
#include "../include/weapon.h"
#include "../include/knife.h"
#include "../include/glock.h"
#include "../include/configuration.h"
#include "../include/game.h"

Weapon* WeaponFactory::create(Game& game, int weapon_id) {
    const Configuration& config = game.getConfig();
    switch(weapon_id) {
        case 1:
            return new Knife(config);
        case 2:
            return new Glock(config);
        default:
            throw new std::exception();
    }
}
