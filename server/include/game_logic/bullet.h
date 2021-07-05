#ifndef BULLET_H
#define BULLET_H

#include "body.h"

class Bomb;
class Block;
class Game;
class Player;
class Weapon;

class Bullet : public Body {
private:
	Player& player;
	Weapon* weapon;
	float initial_x;
	float initial_y;

public:
	Bullet(Game& game, Player& player, Weapon* weapon);
	Bullet(Game& game, Player& player, Weapon* weapon, float angle_offset);

	float getTravelDistance() const;
	float getDamage() const;
	bool isOutOfRange() const;

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
