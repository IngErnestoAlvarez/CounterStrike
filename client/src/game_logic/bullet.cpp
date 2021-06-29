#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/block.h"

Bullet::Bullet(Game& game, Player& player)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle(),
		   game.getConfig().getBulletSpeed()),
	  player(player) {
}

Bullet::Bullet(Game& game, Player& player, float angle_offset)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle() + angle_offset,
		   game.getConfig().getBulletSpeed()),
	  player(player) {
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
