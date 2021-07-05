#include "game_proxy/weapon_proxy.h"

WeaponProxy::WeaponProxy() { maxammo = 30; }

WeaponProxy::~WeaponProxy() {}

int WeaponProxy::getAmmo() { return ammo; }

int WeaponProxy::getMaxAmmo() { return maxammo; }

void WeaponProxy::setAmmo(int ammo) { this->ammo = ammo; }

void WeaponProxy::setWeapon(int weapon) { this->weapon = BodyType(weapon); }
