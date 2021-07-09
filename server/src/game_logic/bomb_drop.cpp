#include "game_logic/bomb_drop.h"
#include "game_logic/game.h"

BombDrop::BombDrop(Game& game, float x, float y)
	: Body(game.getWorld(), BOMB_D_TYPE, x, y, 0, 0) {}

void BombDrop::update() {}

void BombDrop::handleCollision(Body* body) {
	body->handleCollision(this);
}

void BombDrop::handleCollision(Player* player) {
	player->handleCollision(this);
}

void BombDrop::handleCollision(Bullet* bullet) {}

void BombDrop::handleCollision(Block* block) {}

void BombDrop::handleCollision(Bomb* bomb) {}

void BombDrop::handleCollision(WeaponDrop* weapon_drop) {}

void BombDrop::handleCollision(BombDrop* bomb_drop) {}
