#ifndef BULLET_H
#define BULLET_H

#include "body.h"

class Game;
class Player;
class Block;
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
	void handleCollision(Body* body) override;
	void handleCollision(Player* player) override;
	void handleCollision(Bullet* bullet) override;
	void handleCollision(Block* block) override;
	bool isOutOfRange() const;
	void update() override;
};

#endif
