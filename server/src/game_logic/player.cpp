#include "game_logic/block.h"
#include "game_logic/bullet.h"
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/player.h"
#include "game_logic/team.h"
#include "game_logic/weapons/weapon_factory.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/weapon_drop.h"
#include "types.h"
#include "Logger.h"

Player::Player(Game& game,
               int player_id,
               int team_id,
               float x,
               float y)
    : Body(game.getWorld(), TT1_TYPE, x, y, 0,
           game.getConfig().getPlayerSpeed()),
      game(game),
      player_id(player_id),
      team_id(team_id),
      health(game.getConfig().getPlayerHealth()),
      money(game.getConfig().getInitialMoney()),
      ammo(30),
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

BodyType Player::getEquippedWeaponType() {
    return this->equipped_weapon->getType();
}

void Player::changeToPrimaryWeapon() {
    this->equipped_weapon = (this->primary_weapon != nullptr)
        ? this->primary_weapon
        : this->default_melee_weapon;
}

void Player::changeToDMeleeWeapon() {
    this->equipped_weapon = this->default_melee_weapon;
}

void Player::changeToDRangeWeapon() {
    this->equipped_weapon = this->default_range_weapon;
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
    return this->ammo;
}

void Player::useAmmo() {
    this->ammo--;
}

void Player::useWeapon() {
    return this->equipped_weapon->use();
}

bool Player::hasBomb() {
    return this->has_bomb;
}

void Player::receiveBomb() {
    this->has_bomb = true;
}

void Player::activateBomb() {
    if (this->has_bomb) {
        this->game.createBomb(this->getX() + 20, this->getY() + 20);
        this->has_bomb = false;
    }
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

void Player::reset() {
    this->has_bomb = false;
    this->destroy();
    this->initializeBody();
    this->health = this->game.getConfig().getPlayerHealth();
}

void Player::setRole(Role role) {
    if (role == COUNTER_TERRORIST)
        this->setType(CT2_TYPE);
    else
        this->setType(TT1_TYPE);
}

void Player::buyAK47() {
    this->buyWeapon(AK47_TYPE);
}

void Player::buyAWP() {
    this->buyWeapon(AWP_TYPE);
}

void Player::buyM3() {
    this->buyWeapon(M3_TYPE);
}

void Player::buyWeapon(BodyType type) {
    const Configuration& config = this->game.getConfig();
    Weapon* dropped = this->primary_weapon;
    std::string weapon_name;

    switch (type) {
        case AK47_TYPE:
            weapon_name = "ak47";
            break;
        case AWP_TYPE:
            weapon_name = "awp";
            break;
        case M3_TYPE:
            weapon_name = "m3";
            break;
        default:
            return;
    }

    int weapon_price = config.getWeaponConfigValue(weapon_name, "price");
    if (this->money < weapon_price)
        return;
    this->money -= weapon_price;
    this->primary_weapon = WeaponFactory::create(this->game,
                                                 *this,
                                                 weapon_name);
    if (dropped != nullptr)
        this->game.createWeaponDrop(this->getX(), this->getY(), dropped);
}

void Player::buyBullets() {
    // Configuration& config = this->game.getConfig();
    int bullet_stack_size = 10;
    int bullet_stack_price = 0;
    if (this->money < bullet_stack_price)
        return;
    this->money -= bullet_stack_price;
    this->ammo += bullet_stack_size;
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
    if (this->team->getRole() == TERRORIST) {
        this->receiveBomb();
        bomb_drop->setToBeDestroyed();
    }
}

void Player::handleCollision(Bomb* bomb) {
    if (this->team->getRole() == COUNTER_TERRORIST) {
        bomb->deactivate();
    }
}
