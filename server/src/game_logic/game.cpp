#include "game_logic/game.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "command.h"
#include "game_logic/block.h"
#include "game_logic/body.h"
#include "game_logic/bomb.h"
#include "game_logic/bomb_drop.h"
#include "game_logic/player.h"
#include "game_logic/weapon_drop.h"

#ifndef STRINGIZER
#define STRINGIZER(arg) #arg
#define STR_VALUE(arg) STRINGIZER(arg)
#endif
#ifndef APATH
#define APATH STR_VALUE(ASSETSPATH)
#endif

Game::Game(Configuration &config, const std::string &map_filepath)
    : config(config),
      world(*this),
      map(*this, std::string(APATH) + map_filepath),
      round(0),
      phase(TEAMS_FORMING_PHASE),
      winner_team(NONE),
      has_finished(false),
      team_a(*this, TEAM_A, COUNTER_TERRORIST),
      team_b(*this, TEAM_B, TERRORIST),
      preparation_steps(0) {}

void Game::start() { this->initializeTeams(); }

bool Game::isInTeamsFormingPhase() {
    return this->phase == TEAMS_FORMING_PHASE;
}

bool Game::isRunning() { return this->phase != FINAL_PHASE; }

bool Game::addPlayer(TeamID team_id, int peer_id) {
    Team &team = (team_id == TEAM_A) ? this->team_a : this->team_b;

    if (team.isFull()) return false;

    Cell &cell = (team_id == TEAM_A)
                     ? this->map.getStartingCellCounterterrorists()
                     : this->map.getStartingCellTerrorists();

    Player *player =
        new Player(*this, peer_id, team_id, cell.getWorldX(), cell.getWorldY());

    team.addPlayer(player);
    this->players[peer_id] = player;
    this->bodies.push_back(player);

    if (this->team_a.isFull() && this->team_b.isFull())
        this->phase = PREPARATION_PHASE;

    return true;
}

void Game::initializeTeams() {
    this->team_a.initialize();
    this->team_b.initialize();
}

bool Game::canPlayerExecuteCommands(int player_id) {
    return !this->players[player_id]->isDestroyed() &&
           this->players[player_id]->isAlive();
}

void Game::executeCommand(Command &command) {
    Comando code = command.getCode();
    int player_id = command.getPeerID();

    if (!this->canPlayerExecuteCommands(player_id)) return;

    switch (code) {
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
        case CW1:
            if (this->phase == PREPARATION_PHASE)
                this->buyPlayerAK47(player_id);
            else
                this->setWeaponToPrimary(player_id);
            break;
        case CW2:
            if (this->phase == PREPARATION_PHASE)
                this->buyPlayerAWP(player_id);
            else
                this->setWeaponToRange(player_id);
            break;
        case CW3:
            if (this->phase == PREPARATION_PHASE)
                this->buyPlayerM3(player_id);
            else
                this->setWeaponToMelee(player_id);
            break;
        case CB:
            if (this->phase == PREPARATION_PHASE)
                this->buyPlayerBullets(player_id);
            else
                this->activateBomb(player_id);
            break;
        case AIM:
            this->setPlayerAngle(player_id,
                                 command.getArg("angle") * 3.1416 / 180);
            break;
        default:
            break;
    }
}

void Game::movePlayerUp(int player_id) { this->players[player_id]->moveUp(); }

void Game::movePlayerDown(int player_id) {
    this->players[player_id]->moveDown();
}

void Game::movePlayerLeft(int player_id) {
    this->players[player_id]->moveLeft();
}

void Game::movePlayerRight(int player_id) {
    this->players[player_id]->moveRight();
}

void Game::setPlayerAngle(int player_id, float angle) {
    this->players[player_id]->setAngle(angle);
}

void Game::stopPlayer(int player_id) { this->players[player_id]->stopMoving(); }

void Game::usePlayerWeapon(int player_id) {
    this->players[player_id]->useWeapon();
}

void Game::setWeaponToPrimary(int player_id) {
    this->players[player_id]->changeToPrimaryWeapon();
}

void Game::setWeaponToMelee(int player_id) {
    this->players[player_id]->changeToDMeleeWeapon();
}

void Game::setWeaponToRange(int player_id) {
    this->players[player_id]->changeToDRangeWeapon();
}

void Game::activateBomb(int player_id) {
    this->players[player_id]->activateBomb();
}

void Game::buyPlayerAK47(int player_id) {
    this->players[player_id]->buyAK47();
}

void Game::buyPlayerAWP(int player_id) {
    this->players[player_id]->buyAWP();
}

void Game::buyPlayerM3(int player_id) {
    this->players[player_id]->buyM3();
}

void Game::buyPlayerBullets(int player_id) {
    this->players[player_id]->buyBullets();
}

void Game::createBomb(float x, float y) {
    Bomb *bomb = new Bomb(*this, x, y);
    this->bomb = bomb;
    // this->bodies.push_back(bomb);
}

void Game::createWeaponDrop(float x, float y, Weapon *weapon) {
    WeaponDrop *weapon_drop = new WeaponDrop(*this, x, y);
    weapon_drop->setWeapon(weapon);
    this->bodies.push_back(weapon_drop);
}

void Game::createBombDrop(float x, float y) {
    this->bodies.push_back(new BombDrop(*this, x, y));
}

void Game::createBlock(float x, float y) {
    this->bodies.push_back(new Block(*this, x, y));
}

std::vector<Body *> Game::getBodies(int peer_id) {
    Player *player = this->players[peer_id];
    std::vector<Body *> bodies;

    for (Body *body : this->bodies)
        if (!body->isDestroyed() && body->getID() != player->getID())
            bodies.push_back(body);

    if (this->bomb != nullptr) bodies.push_back(this->bomb);

    return bodies;
}

int Game::getX() { return int(this->player->getX()); }

int Game::getY() { return int(this->player->getY()); }

int Game::getAngle() { return int(this->player->getAngle()); }

World &Game::getWorld() { return this->world; }

Map &Game::getMap() { return this->map; }

const Configuration &Game::getConfig() { return this->config; }

bool Game::hasBombBeenDeactivated() {
    return this->bomb != nullptr && this->bomb->isDestroyed();
}

bool Game::hasBombExploded() {
    return this->bomb != nullptr && this->bomb->hasExploded();
}

void Game::checkBombState() {
    TeamID counter_terrorists =
        this->team_a.getRole() == COUNTER_TERRORIST ? TEAM_A : TEAM_B;
    TeamID terrorists = counter_terrorists == TEAM_A ? TEAM_B : TEAM_A;

    if (this->hasBombBeenDeactivated()) {
        this->winner_team = counter_terrorists;
    } else if (this->hasBombExploded()) {
        this->winner_team = terrorists;
    }
}

void Game::checkTeamsState() {
    if (!this->team_a.hasPlayersAlive())
        this->winner_team = TEAM_B;
    else if (!this->team_b.hasPlayersAlive())
        this->winner_team = TEAM_A;
}

Phase Game::getPhase() { return this->phase; }

void Game::goToNextRound() {
    this->round++;

    if (this->round == this->final_round) {
        this->phase = FINAL_PHASE;
        int team_a_win_count = this->team_a.getWinCount();
        int team_b_win_count = this->team_b.getWinCount();

        if (team_a_win_count == team_b_win_count)
            this->winner_team = NONE;
        else if (team_a_win_count > team_b_win_count)
            this->winner_team = TEAM_A;
        else
            this->winner_team = TEAM_B;
    } else {
        this->phase = PREPARATION_PHASE;
        this->winner_team = NONE;

        if (this->round == int(this->final_round / 2)) {
            this->team_a.switchRole();
            this->team_b.switchRole();
        }

        for (auto &player : this->players) player.second->reset();
        this->initializeTeams();

        if (this->bomb != nullptr)
            // delete this->bomb;
            this->bomb = nullptr;
    }
}

void Game::step() {
    if (!this->isRunning()) return;

    switch (this->phase) {
        case PREPARATION_PHASE:
            this->preparation_steps++;
            if (this->preparation_steps == 50) {
                this->preparation_steps = 0;
                this->phase = MAIN_PHASE;
            }
            break;
        case MAIN_PHASE:
            if (this->winner_team != NONE) {
                this->goToNextRound();
            } else {
                this->world.step();
                this->checkBombState();
                this->checkTeamsState();
                this->team_a.update();
                this->team_b.update();
            }
            break;
        case FINAL_PHASE:
            break;
        default:
            break;
    }
}

GameState Game::getState(int player_id) { return GameState(*this, player_id); }

TeamID Game::getWinnerTeam() { return this->winner_team; }

int Game::getTeamAWins() const { return this->team_a.getWinCount(); }

int Game::getTeamBWins() const { return this->team_b.getWinCount(); }

Game::~Game() {
    for (Body *body : this->bodies) delete body;

    if (this->bomb != nullptr) delete this->bomb;
}

Player *Game::getPlayer(int player_id) { return this->players[player_id]; }

int Game::getTeamASize() {
    return this->team_a.getSize();
}

int Game::getTeamBSize() {
    return this->team_b.getSize();
}

std::vector<Player*>& Game::getTeamAPlayers() {
    return this->team_a.getPlayers();
}

std::vector<Player*>& Game::getTeamBPlayers() {
    return this->team_b.getPlayers();
}

// ----------- estos metodos se eliminarian ------------

Player *Game::createPlayer(float x, float y) {
    if (this->player != nullptr) return nullptr;

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

void Game::useWeapon() { this->player->useWeapon(); }
