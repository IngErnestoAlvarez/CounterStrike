#ifndef __MODELO_LOGIC_H__
#define __MODELO_LOGIC_H__

#include "game_logic/game.h"
#include "game_logic/map.h"
#include "game_logic/world.h"

class ModeloLogic {
   private:
    Game game;

   public:
    ModeloLogic();

    ~ModeloLogic();

    void update();

    World &getWorld();
    Map &getMap();
};

#endif  // __MODELO_LOGIC_H__
