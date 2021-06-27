#ifndef BULLET_H
#define BULLET_H

#include "body.h"

class Game;
class Player;

class Bullet : public Body {
public:
	Bullet(Game& game, Player& player);
	Bullet(Game& game, Player& player, float angle_offset);
};

#endif
