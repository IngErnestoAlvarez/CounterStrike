#include "game_logic/weapons/weapon.h"

#include "configuration.h"
#include "game_logic/body.h"
#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/world.h"

Weapon::Weapon(const std::string &name, BodyType type, Game &game,
               Player &player)
    : name(name), game(game), world(game.getWorld()), player(player) {
    const Configuration &config = game.getConfig();
    this->damage = config.getWeaponConfigValue(name, "damage");
    this->precision = config.getWeaponConfigValue(name, "precision");
    this->range = config.getWeaponConfigValue(name, "range");
    // this->ammo = config.getWeaponConfigValue(name, "initial_ammo");
    this->type = type;
}

Weapon::~Weapon() {}

std::string Weapon::getName() const { return this->name; }

int Weapon::getAmmo() const { return this->player.getAmmo(); }

float Weapon::getRange() const { return this->range; }

void Weapon::createBullet() { this->createBullet(0); }

void Weapon::createBullet(float angle) {
    Bullet *bullet = nullptr;

    if (this->getAmmo() > 0) {
        bullet = new Bullet(this->game, this->player, this, angle);
        this->active_bullets.insert(bullet);
        bullet->move();
        this->player.useAmmo();
    }
}

void Weapon::deleteInactiveBullets() {
    for (auto it = this->active_bullets.begin();
         it != this->active_bullets.end();) {
        if ((*it)->isDestroyed()) {
            delete *it;
            this->active_bullets.erase(it);
        }

        ++it;
    }
}

float Weapon::getDamage(float distance) const { return 10; }

BodyType Weapon::getType() { return this->type; }
