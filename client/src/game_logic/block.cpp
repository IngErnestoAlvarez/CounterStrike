#include "game_logic/block.h"
#include "game_logic/game.h"
#include "game_logic/bullet.h"
#include "game_logic/player.h"

Block::Block(Game& game, float x, float y)
	: Body(game.getWorld(), x, y, 0, 0) {
}

void Block::handleCollision(Body* body) {
	body->handleCollision(this);
}

void Block::handleCollision(Block* block) {}

void Block::handleCollision(Bullet* bullet) {
	bullet->setToBeDestroyed();
}

void Block::handleCollision(Player* player) {}
