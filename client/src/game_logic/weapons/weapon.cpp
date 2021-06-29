#include "game_logic/body.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/player.h"
#include "game_logic/world.h"
#include "game_logic/game.h"
#include "game_logic/bullet.h"
#include "configuration.h"

Weapon::Weapon(const std::string& name,
               Game& game,
               Player& player)
             : name(name),
               game(game),
               world(game.getWorld()),
               player(player) {
    const Configuration& config = game.getConfig();
    this->damage = config.getWeaponConfigValue(name, "damage");
    this->precision = config.getWeaponConfigValue(name, "precision");
    this->range = config.getWeaponConfigValue(name, "range");
    this->ammo = config.getWeaponConfigValue(name, "initial_ammo");
}

Weapon::~Weapon() {}

std::string Weapon::getName() const {
    return this->name;
}

int Weapon::getAmmo() const {
    return this->ammo;
}

void Weapon::createBullet() {
    this->createBullet(0);
}

void Weapon::createBullet(float angle) {
    Bullet* bullet = nullptr;

    if (this->ammo > 0) {
        bullet = new Bullet(this->game, this->player, angle);
        this->active_bullets.insert(bullet);
        bullet->move();
    }

    this->ammo--;
}

void Weapon::deleteInactiveBullets() {
    for (auto it = this->active_bullets.begin(); it != this->active_bullets.end();) {
        if ((*it)->toBeDestroyed()) {
            delete *it;
            this->active_bullets.erase(it);
        }

        ++it;
    }
}
