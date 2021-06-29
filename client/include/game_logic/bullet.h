#ifndef BULLET_H
#define BULLET_H

#include "body.h"

class Game;
class Player;
class Block;

class Bullet : public Body {
private:
	Player& player;
public:
	Bullet(Game& game, Player& player);
	Bullet(Game& game, Player& player, float angle_offset);
	void handleCollision(Body* body) override;
	void handleCollision(Player* player) override;
	void handleCollision(Bullet* bullet) override;
	void handleCollision(Block* block) override;
};

#endif
