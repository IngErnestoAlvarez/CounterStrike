#include "game_logic/bomb.h"
#include "game_logic/game.h"
#include "types.h"
#include "Logger.h"

Bomb::Bomb(Game& game, float x, float y)
	: Body(game.getWorld(), BOMB_D_TYPE, x, y, 0, 0),
	  active(true),
	  has_exploded(false),
	  max_steps(100000), // obtener de configuracion
	  steps(0) {
	using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se planta la bomba");
}

void Bomb::update() {
	this->has_exploded = false;

	if (this->hasBeenDeactivated())
		return;

	this->steps++;

	using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se actualiza la bomba");

	if (this->steps == max_steps) {
		log->debug("Explota la bomba");
		this->explode();
	}
}

void Bomb::explode() {
	this->has_exploded = true;
	this->setToBeDestroyed();
}

void Bomb::deactivate() {
	this->active = false;
	this->setToBeDestroyed();
}

bool Bomb::hasExploded() const {
	return this->has_exploded;
}

bool Bomb::hasBeenDeactivated() const {
	return !this->active;
}

void Bomb::handleCollision(Body* body) {
	body->handleCollision(this);
}

void Bomb::handleCollision(Player* player) {
	player->handleCollision(this);
}

void Bomb::handleCollision(Bullet* bullet) {}

void Bomb::handleCollision(Block* block) {}

void Bomb::handleCollision(Bomb* bomb) {}

void Bomb::handleCollision(WeaponDrop* weapon_drop) {}

void Bomb::handleCollision(BombDrop* bomb_drop) {}
