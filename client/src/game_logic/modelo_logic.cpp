#include "game_logic/modelo_logic.h"

#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/world.h"

ModeloLogic::ModeloLogic()
    : game("config/config.yaml", "assets/maps/map.yaml") {
    this->game.createPlayer(400, 300);
}

ModeloLogic::~ModeloLogic() {}

void ModeloLogic::update() { game.step(); }

World &ModeloLogic::getWorld() { return game.getWorld(); }

Map &ModeloLogic::getMap() { return game.getMap(); }

std::vector<Body *> &ModeloLogic::getBodies() {
    return this->game.getWorld().getBodies();
}

Player *ModeloLogic::getPlayer() { return this->game.getPlayer(); }

void ModeloLogic::movePlayerUp() { game.moveUp(); }

void ModeloLogic::movePlayerDown() { game.moveDown(); }

void ModeloLogic::movePlayerLeft() { game.moveLeft(); }

void ModeloLogic::movePlayerRight() { game.moveRight(); }

void ModeloLogic::setPlayerAim(int x, int y) { game.setAim(x, y); }

void ModeloLogic::stopPlayer() { game.stopMoving(); }

int ModeloLogic::getPlayerX() { return this->game.getX(); }

int ModeloLogic::getPlayerY() { return this->game.getY(); }

int ModeloLogic::getPlayerAngle() { return this->game.getAngle(); }
