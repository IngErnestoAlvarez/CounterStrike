#ifndef BOMB_H
#define BOMB_H

#include "body.h"

class Block;
class Bomb;
class BombDrop;
class Bullet;
class Game;
class Player;
class WeaponDrop;

class Bomb : public Body {
private:
	bool active;
	bool has_exploded;
	int max_steps;
	int steps;

public:
	Bomb(Game& game, float x, float y);

	void explode();
	void deactivate();

	bool hasExploded() const;
	bool hasBeenDeactivated() const;

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
