#include "game_logic/block.h"
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/weapon_drop.h"
#include "types.h"

Block::Block(Game& game,
			 float x,
			 float y)
	: Body(game.getWorld(), WALL_TYPE, x, y, 0, 0) {
}

void Block::handleCollision(Body* body) {
	body->handleCollision(this);
}

void Block::handleCollision(Bullet* bullet) {
	bullet->setToBeDestroyed();
}

void Block::handleCollision(Block* block) {}

void Block::handleCollision(Player* player) {}

void Block::handleCollision(Bomb* bomb) {}

void Block::handleCollision(WeaponDrop* weapon_drop) {}

void Block::handleCollision(BombDrop* bomb_drop) {}
