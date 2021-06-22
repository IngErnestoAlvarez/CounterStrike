#include "game_logic/game.h"

#include "game_logic/player.h"

Game::Game(const std::string &config_filepath, const std::string &map_filepath)
    : config(config_filepath), world(), map(&world, map_filepath) {}

// void Game::moveUp(int player_id) { this->players.at(player_id).moveUp(); }

// void Game::moveDown(int player_id) { this->players.at(player_id).moveDown(); }

// void Game::moveLeft(int player_id) { this->players.at(player_id).moveLeft(); }

// void Game::moveRight(int player_id) { this->players.at(player_id).moveRight(); }

World &Game::getWorld() { return this->world; }

Map &Game::getMap() { return this->map; }

const Configuration &Game::getConfig() { return this->config; }

Game::~Game() {}
