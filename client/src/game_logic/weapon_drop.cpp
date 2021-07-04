#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapon_drop.h"
#include "types.h"

WeaponDrop::WeaponDrop(Game& game, float x, float y)
: Body(game.getWorld(), AK47_D_TYPE, x, y, 0, 0),
	  weapon(nullptr) {}

WeaponDrop::~WeaponDrop() {
	if (this->weapon != nullptr)
		delete this->weapon;
}

void WeaponDrop::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}

Weapon* WeaponDrop::getWeapon() {
	Weapon* weapon = this->weapon;
	this->weapon = nullptr;
	return weapon;
}

void WeaponDrop::update() {}

void WeaponDrop::handleCollision(Body* body) {
	body->handleCollision(this);
}

void WeaponDrop::handleCollision(Player* player) {
	player->handleCollision(this);
}

void WeaponDrop::handleCollision(Bullet* bullet) {
	bullet->setToBeDestroyed();
}

void WeaponDrop::handleCollision(Block* block) {}

void WeaponDrop::handleCollision(Bomb* bomb) {}

void WeaponDrop::handleCollision(WeaponDrop* weapon_drop) {}

void WeaponDrop::handleCollision(BombDrop* bomb_drop) {}
