#include "game_logic/game.h"

#include <cmath>
#include <iostream>

#include "game_logic/body.h"
#include "game_logic/player.h"

Game::Game(const std::string &config_filepath, const std::string &map_filepath)
    : config(config_filepath), world(*this), map(world, map_filepath) {}

void Game::moveUp() { this->player->moveUp(); }

void Game::moveDown() { this->player->moveDown(); }

void Game::moveLeft() { this->player->moveLeft(); }

void Game::moveRight() { this->player->moveRight(); }

void Game::setAim(int x, int y) {
    this->player->setAngle(
        (atan2(this->player->getY() - y, this->player->getX() - x) * 180.0000) /
            3.1416 +
        90);
}

void Game::stopMoving() { this->player->stopMoving(); }

void Game::useWeapon() {
    this->player->useWeapon();
}

int Game::getX() { return int(this->player->getX()); }

int Game::getY() { return int(this->player->getY()); }

int Game::getAngle() { return int(this->player->getAngle()); }

World &Game::getWorld() { return this->world; }

Map &Game::getMap() { return this->map; }

const Configuration &Game::getConfig() { return this->config; }

Player *Game::createPlayer(float x, float y) {
    if (this->player != nullptr)
        return nullptr;

    this->player = new Player(*this, 0, x, y);
    return this->player;
}

void Game::step() {
    this->world.step();
}

Game::~Game() {
    if (this->player != nullptr)
        delete this->player;
}

Player *Game::getPlayer() { return this->player; }
