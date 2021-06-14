#include "player.h"
#include "map.h"
#include "weapon_factory.h"
#include "game.h"

Player::Player(Game& game, int x, int y) : game(game), x(x), y(y) {}

void Player::move(int x_target, int y_target) {
    Map& map = this->game.getMap();
    if (!map.canBeAccesed(x_target, y_target)) {
        return;
    }

    this->x = x_target;
    this->y = y_target;

    int weapon_id = map.getWeaponAt(x_target, y_target);

    if (weapon_id > 0) {
        this->addWeaponToInventory(weapon_id);
    }
}

void Player::moveUp() {
    this->move(this->x, this->y - 1);
}

void Player::moveDown() {
    this->move(this->x, this->y + 1);
}

void Player::moveLeft() {
    this->move(this->x - 1, this->y);
}

void Player::moveRight() {
    this->move(this->x + 1, this->y);
}

void Player::addWeaponToInventory(int weapon_id) {
    this->inventory.push_back(WeaponFactory::create(this->game, weapon_id));
}

int Player::getX() const {
    return this->x;
}

int Player::getY() const {
    return this->y;
}
