#ifndef WEAPON_DROP_H
#define WEAPON_DROP_H

#include "body.h"

class Block;
class Bomb;
class BombDrop;
class Bullet;
class Game;
class Player;
class Weapon;

class WeaponDrop : public Body {
private:
	Weapon* weapon;

public:
	WeaponDrop(Game& game, float x, float y);
	~WeaponDrop();

	void setWeapon(Weapon* weapon);
	Weapon* getWeapon();

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
