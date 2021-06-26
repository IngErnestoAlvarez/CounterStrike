#include "game_logic/game.h"

#include <cmath>
#include <iostream>

#include "game_logic/body.h"
#include "game_logic/player.h"

Game::Game(const std::string &config_filepath, const std::string &map_filepath)
    : config(config_filepath), world(), map(world, map_filepath) {}

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

int Game::getX() { return int(this->player->getX()); }

int Game::getY() { return int(this->player->getY()); }

int Game::getAngle() { return int(this->player->getAngle()); }

World &Game::getWorld() { return this->world; }

Map &Game::getMap() { return this->map; }

const Configuration &Game::getConfig() { return this->config; }

Body *Game::createPlayer(float x, float y) {
    if (this->player != nullptr) {
        throw std::runtime_error(
            "Se intento crear personaje pero el mismo ya existia");
    }

    this->player = this->world.createBody(x, y, this->config.getPlayerSpeed());
    return this->player;
}

void Game::step() { this->world.step(); }

Game::~Game() {}

Player *Game::getPlayer() { return (Player *)this->player; }
