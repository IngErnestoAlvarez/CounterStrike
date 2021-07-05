#include "game_logic/block.h"
#include "game_logic/bullet.h"
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/player.h"
#include "game_logic/team.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/weapon_drop.h"
#include "types.h"

Player::Player(Game& game,
               int player_id,
               int team_id,
               float x,
               float y)
    : Body(game.getWorld(), CT2_TYPE, x, y, 0,
           game.getConfig().getPlayerSpeed()),
      game(game),
      player_id(player_id),
      team_id(team_id),
      health(game.getConfig().getPlayerHealth()),
      money(game.getConfig().getInitialMoney()),
      kill_reward(game.getConfig().getKillReward()),
      primary_weapon(nullptr) {
    default_melee_weapon = new Knife(game, *this);
    default_range_weapon = new Glock(game, *this);
    equipped_weapon = default_range_weapon;
}

Player::~Player() {
    if (default_melee_weapon != nullptr
        && default_melee_weapon != equipped_weapon)
        delete default_melee_weapon;

    if (default_range_weapon != nullptr
        && default_range_weapon != equipped_weapon)
        delete default_range_weapon;

    if (primary_weapon != nullptr
        && primary_weapon != equipped_weapon)
        delete primary_weapon;

    if (equipped_weapon != nullptr)
        delete equipped_weapon;
}

void Player::addWeapon(Weapon* weapon) {
    if (this->primary_weapon != nullptr)
        this->game.createWeaponDrop(this->getX(),
                                    this->getY(),
                                    this->primary_weapon);
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

void Player::receiveBomb() {
    this->has_bomb = true;
}

void Player::activateBomb() {
    if (this->has_bomb)
        this->game.createBomb(this->getX(), this->getY());
}

void Player::registerTeam(Team* team) {
    this->team = team;
}

bool Player::isTerrorist() const {
    return this->team->getRole() == 2;
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

void Player::handleCollision(WeaponDrop* weapon_drop) {
    Weapon* weapon = weapon_drop->getWeapon();
    weapon_drop->setWeapon(this->primary_weapon);

    if (this->primary_weapon == this->equipped_weapon)
        this->equipped_weapon = weapon;

    this->primary_weapon = weapon;
}

void Player::handleCollision(BombDrop* bomb_drop) {
    if (this->team->getRole() == 1) {
        this->receiveBomb();
        bomb_drop->setToBeDestroyed();
    }
}

void Player::handleCollision(Bomb* bomb) {
    if (this->team->getRole() == 2) {
        bomb->setToBeDestroyed();
    }
}
