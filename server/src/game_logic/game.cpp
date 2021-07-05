#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "game_logic/block.h"
#include "game_logic/body.h"
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/weapon_drop.h"

Game::Game(const std::string &config_filepath,
           const std::string &map_filepath)
    : config(config_filepath),
      world(*this),
      map(*this, map_filepath),
      round(0),
      phase(TEAMS_FORMING_PHASE),
      winner_team(NO_ROLE),
      has_finished(false),
      team_a(*this, COUNTER_TERRORIST),
      team_b(*this, TERRORIST) {}

void Game::start() {
    this->phase = MAIN_PHASE;
    this->assignBombToRandomPlayer();
}

int Game::addPlayer(TeamID team_id) {
    if (this->phase != TEAMS_FORMING_PHASE)
        return 0;

    Cell& cell = (team_id == TEAM_A)
               ? this->map.getStartingCellAntiterrorists()
               : this->map.getStartingCellTerrorists();

    int player_id = this->players.size();
    Player* player = new Player(*this,
                                player_id,
                                team_id,
                                cell.getWorldX(),
                                cell.getWorldY());
    this->players.push_back(player);

    if (team_id == TEAM_A)
        this->team_a.addPlayer(player);
    else
        this->team_b.addPlayer(player);

    return player_id;
}

void Game::assignBombToRandomPlayer() {
    std::vector<Player*> terrorists;
    std::copy_if(this->players.begin(),
                 this->players.end(),
                 std::back_inserter(terrorists),
                 [](const Player* p) {
                    return p->isTerrorist();
                });

    int index = rand() % terrorists.size();
    terrorists[index]->receiveBomb();
}

void Game::executeCommand(int player_id, Comando command) {
    switch (command) {
        case UP:
            this->movePlayerUp(player_id);
            break;
        case DOWN:
            this->movePlayerDown(player_id);
            break;
        case LEFT:
            this->movePlayerLeft(player_id);
            break;
        case RIGHT:
            this->movePlayerRight(player_id);
            break;
        case SHOOT:
            this->usePlayerWeapon(player_id);
            break;
        case STOP:
            this->stopPlayer(player_id);
            break;
        default:
            break;
    }
}

void Game::movePlayerUp(int player_id) {
    this->players[player_id]->moveUp();
}

void Game::movePlayerDown(int player_id) {
    this->players[player_id]->moveDown();
}

void Game::movePlayerLeft(int player_id) {
    this->players[player_id]->moveLeft();
}

void Game::movePlayerRight(int player_id) {
    this->players[player_id]->moveRight();
}

void Game::setPlayerAim(int player_id, int x, int y) {
    this->players[player_id]->setAngle(
        (atan2(this->player->getY() - y, this->player->getX() - x) * 180.0000) /
            3.1416 +
        90);
}

void Game::stopPlayer(int player_id) {
    this->players[player_id]->stopMoving();
}

void Game::usePlayerWeapon(int player_id) {
    this->players[player_id]->useWeapon();
}

void Game::createBomb(float x, float y) {
    Bomb* bomb = new Bomb(*this, x, y);
    this->bomb = bomb;
    this->bodies.push_back(bomb);
}

void Game::createWeaponDrop(float x, float y, Weapon* weapon) {
    WeaponDrop* weapon_drop = new WeaponDrop(*this, x, y);
    weapon_drop->setWeapon(weapon);
    this->bodies.push_back(weapon_drop);
}

void Game::createBombDrop(float x, float y) {
    this->bodies.push_back(new BombDrop(*this, x, y));
}

void Game::createBlock(float x, float y) {
    this->bodies.push_back(new Block(*this, x, y));
}

std::vector<Body*>& Game::getBodies() {
    return this->bodies;
}

int Game::getX() { return int(this->player->getX()); }

int Game::getY() { return int(this->player->getY()); }

int Game::getAngle() { return int(this->player->getAngle()); }

World &Game::getWorld() { return this->world; }

Map &Game::getMap() { return this->map; }

const Configuration &Game::getConfig() { return this->config; }

bool Game::hasBombBeenDeactivated() {
    return this->bomb != nullptr
        && this->bomb->isDestroyed();
}

bool Game::hasBombExploded() {
    return this->bomb != nullptr
        && this->bomb->hasExploded();
}

void Game::checkBombState() {
    if (this->hasBombBeenDeactivated()) {
        this->winner_team = COUNTER_TERRORIST;
    } else if (this->hasBombExploded()) {
        this->winner_team = TERRORIST;
    }
}

void Game::checkTeamsState() {
    if (!this->team_a.hasPlayersAlive())
        this->winner_team = this->team_b.getRole();
    else if (!this->team_b.hasPlayersAlive())
        this->winner_team = this->team_a.getRole();
}

void Game::goToNextRound() {
    this->round++;
    this->phase = PREPARATION_PHASE;
    this->winner_team = NO_ROLE;

    if (this->round == int(this->final_round / 2)) {
        this->team_a.switchRole();
        this->team_b.switchRole();
    }
}

void Game::step() {
    if (this->has_finished)
        return;

    // if (this->winner_team) {
    //     this->nextRound();
    //     return;
    // }

    this->world.step();
    this->checkBombState();
    this->checkTeamsState();

    this->team_a.update();
    this->team_b.update();

    // if (this->round > this->final_round)
    //     this->has_finished = true;
}

Role Game::getWinnerTeam() {
    return this->winner_team;
}

Game::~Game() {
    if (this->player != nullptr)
        delete this->player;

    for (Body* body : this->bodies)
        delete body;
}

// ----------- estos metodos se eliminarian ------------

Player *Game::createPlayer(float x, float y) {
    if (this->player != nullptr)
        return nullptr;

    this->player = new Player(*this, 0, 0, x, y);
    return this->player;
}

Player *Game::getPlayer() { return this->player; }

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
