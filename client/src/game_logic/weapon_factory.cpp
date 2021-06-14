#include "weapon_factory.h"
#include "weapon.h"
#include "knife.h"
#include "glock.h"
#include "configuration.h"
#include "game.h"

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
