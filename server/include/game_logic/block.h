#ifndef BLOCK_H
#define BLOCK_H

#include "body.h"

class Bomb;
class BombDrop;
class Bullet;
class Game;
class Player;
class WeaponDrop;

class Block : public Body {
public:
	Block(Game& game, float x, float y);

	void handleCollision(Body* body) override;
	void handleCollision(Block* block) override;
	void handleCollision(Bullet* bullet) override;
	void handleCollision(Player* player) override;
	void handleCollision(Bomb* bomb) override;
	void handleCollision(WeaponDrop* weapon_drop) override;
	void handleCollision(BombDrop* bomb_drop) override;
};

#endif
