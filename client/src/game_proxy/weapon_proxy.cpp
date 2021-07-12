#include "game_proxy/weapon_proxy.h"

#include <mutex>

typedef std::lock_guard<std::mutex> guard;

WeaponProxy::WeaponProxy() : weapon(AK47_TYPE) { maxammo = 30; }

WeaponProxy::~WeaponProxy() {}

int WeaponProxy::getAmmo() {
    guard guard(mutex);
    return ammo;
}

int WeaponProxy::getMaxAmmo() {
    guard guard(mutex);
    return maxammo;
}

void WeaponProxy::setAmmo(int ammo) {
    guard guard(mutex);
    this->ammo = ammo;
}

void WeaponProxy::setWeapon(int weapon) {
    guard guard(mutex);
    this->weapon = BodyType(weapon);
}

BodyType WeaponProxy::getBodyType() {
    guard guard(mutex);
    return weapon;
}
