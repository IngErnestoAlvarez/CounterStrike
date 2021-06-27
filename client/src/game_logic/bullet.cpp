#include "game_logic/bullet.h"
#include "game_logic/game.h"
#include "game_logic/player.h"

Bullet::Bullet(Game& game, Player& player)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle(),
		   game.getConfig().getBulletSpeed()) {
}

Bullet::Bullet(Game& game, Player& player, float angle_offset)
	: Body(game.getWorld(),
		   player.getX(),
		   player.getY(),
		   player.getAngle() + angle_offset,
		   game.getConfig().getBulletSpeed()) {
}
