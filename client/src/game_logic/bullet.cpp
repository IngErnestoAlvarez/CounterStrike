#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/block.h"
#include <Box2D/Box2D.h>
#include "game_logic/weapons/weapon.h"

Bullet::Bullet(Game& game, Player& player, Weapon* weapon)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle(),
		   game.getConfig().getBulletSpeed()),
	  player(player),
	  weapon(weapon),
	  initial_x(player.getX()),
	  initial_y(player.getY()) {
}

Bullet::Bullet(Game& game, Player& player, Weapon* weapon, float angle_offset)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle() + angle_offset,
		   game.getConfig().getBulletSpeed()),
	  player(player),
	  weapon(weapon),
	  initial_x(player.getX()),
	  initial_y(player.getY()) {
}

void Bullet::handleCollision(Body* body) {
	body->handleCollision(this);
	this->setToBeDestroyed();
}

void Bullet::handleCollision(Player* player) {
	if (this->player.getTeamID() != player->getTeamID()) {
		float damage = 10;
		player->takeDamage(damage);

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

bool Bullet::isOutOfRange() const {
	b2Vec2 initial_position(this->initial_x, this->initial_y);
	b2Vec2 current_position(this->getX(), this->getY());
	b2Vec2 difference(current_position - initial_position);

	return difference.Length() > this->weapon->getRange();
}

void Bullet::update() {
	if (!this->isDestroyed() && this->isOutOfRange())
		this->setToBeDestroyed();
}
