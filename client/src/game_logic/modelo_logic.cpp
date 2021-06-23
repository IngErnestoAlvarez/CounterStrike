#include "game_logic/modelo_logic.h"

#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/world.h"

ModeloLogic::ModeloLogic()
    : game("config/config.yaml", "assets/maps/map.yaml") {}

ModeloLogic::~ModeloLogic() {}

void ModeloLogic::update() {}

World &ModeloLogic::getWorld() { return game.getWorld(); }

Map &ModeloLogic::getMap() { return game.getMap(); }
