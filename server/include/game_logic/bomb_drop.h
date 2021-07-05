#ifndef BOMB_DROP_H
#define BOMB_DROP_H

#include "body.h"

class Game;
class Player;
class Bullet;
class Block;
class Bomb;
class WeaponDrop;
class BombDrop;

class BombDrop : public Body {
public:
	BombDrop(Game& game, float x, float y);

	void handleCollision(Body* body) override;
	void handleCollision(Player* player) override;
	void handleCollision(Bullet* bullet) override;
	void handleCollision(Block* block) override;
	void handleCollision(Bomb* bomb) override;
	void handleCollision(WeaponDrop* weapon_drop) override;
	void handleCollision(BombDrop* bomb_drop) override;
	void update() override;
};

#endif
