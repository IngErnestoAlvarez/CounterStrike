#ifndef BLOCK_H
#define BLOCK_H

#include "body.h"

class Game;
class Body;
class Bullet;
class Player;

class Block : public Body {
public:
	Block(Game& game, float x, float y);
	void handleCollision(Body* body) override;
	void handleCollision(Block* block) override;
	void handleCollision(Bullet* bullet) override;
	void handleCollision(Player* player) override;
};

#endif
