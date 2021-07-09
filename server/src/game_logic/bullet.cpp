#include <Box2D/Box2D.h>
#include <iostream>
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/block.h"
#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapon_drop.h"
#include "types.h"
#include <cmath>

Bullet::Bullet(Game& game,
			   Player& player,
			   Weapon* weapon)
	: Body(game.getWorld(),
		   NO_BODY_TYPE,
		   player.getX() + 50 * cos(player.getAngle()),
		   player.getY() + 50 * sin(player.getAngle()),
		   player.getAngle(),
		   game.getConfig().getBulletSpeed()),
	  player(player),
	  weapon(weapon) {}

Bullet::Bullet(Game& game,
			   Player& player,
			   Weapon* weapon,
			   float angle_offset)
	: Body(game.getWorld(),
		   NO_BODY_TYPE,
		   player.getX() + 50 * cos(player.getAngle() + angle_offset),
		   player.getY() + 50 * sin(player.getAngle() + angle_offset),
		   player.getAngle() + angle_offset,
		   game.getConfig().getBulletSpeed()),
	  player(player),
	  weapon(weapon) {}

void Bullet::handleCollision(Body* body) {
	body->handleCollision(this);
	this->setToBeDestroyed();
}

float Bullet::getTravelDistance() const {
	b2Vec2 initial_position(this->initial_x, this->initial_y);
	b2Vec2 current_position(this->getX(), this->getY());
	b2Vec2 difference(current_position - initial_position);
	return difference.Length();
}

float Bullet::getDamage() const {
	return this->weapon->getDamage(this->getTravelDistance());
}

void Bullet::handleCollision(Player* player) {
	if (this->toBeDestroyed())
		return;

	if (player->getTeamID() != this->player.getTeamID()) {
		player->takeDamage(this->getDamage());

		if (!player->isAlive())
			this->player.handleEnemyKilled();
	}

	this->setToBeDestroyed();
}

void Bullet::handleCollision(Bullet* bullet) {
	bullet->setToBeDestroyed();
	this->setToBeDestroyed();
}

void Bullet::handleCollision(Block* block) {
	this->setToBeDestroyed();
}

void Bullet::handleCollision(Bomb* bomb) {
	this->setToBeDestroyed();
}

void Bullet::handleCollision(BombDrop* bomb_drop) {
	this->setToBeDestroyed();
}

void Bullet::handleCollision(WeaponDrop* weapon_drop) {
	this->setToBeDestroyed();
}

bool Bullet::isOutOfRange() const {
	return this->getTravelDistance() > this->weapon->getRange();
}

void Bullet::update() {
	// if (!this->isDestroyed() && this->isOutOfRange())
	// 	this->setToBeDestroyed();
}
