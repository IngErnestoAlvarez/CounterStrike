#include "game_logic/player.h"

#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/bullet.h"
#include "game_logic/block.h"

#define INITIAL_PLAYER_ANGLE 0

Player::Player(Game& game, int team_id, float x, float y)
    : Body(game.getWorld(),
           x, y,
           INITIAL_PLAYER_ANGLE,
           game.getConfig().getPlayerSpeed()),
      team_id(team_id),
      health(game.getConfig().getPlayerHealth()),
      money(game.getConfig().getInitialMoney()),
      kill_reward(game.getConfig().getKillReward()),
      primary_weapon(nullptr) {
    default_melee_weapon = new Knife(game, *this);
    default_range_weapon = new Glock(game, *this);
    equipped_weapon = default_range_weapon;
}

void Player::addWeaponToInventory(Weapon* weapon) {
    // terminar este metodo
    this->primary_weapon = weapon;
}

Weapon* Player::getEquippedWeapon() {
    return this->equipped_weapon;
}

int Player::getTeamID() const {
    return this->team_id;
}

bool Player::isAlive() const {
    return this->health > 0;
}

int Player::getHealth() const {
    return this->health;
}

int Player::getAmmo() const {
    return this->equipped_weapon->getAmmo();
}

void Player::useWeapon() {
    return this->equipped_weapon->use();
}

void Player::takeDamage(float damage) {
    this->health -= damage;
    if (!this->isAlive())
        this->setToBeDestroyed();
}

void Player::handleEnemyKilled() {
    this->money += this->kill_reward;
}

void Player::handleCollision(Body* body) {
    body->handleCollision(this);
}

void Player::handleCollision(Bullet* bullet) {
    bullet->handleCollision(this);
}

void Player::handleCollision(Player* player) {}

void Player::handleCollision(Block* block) {}
