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

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();
    void setPlayerAim(int x, int y);
    void stopPlayer();

    int getPlayerX();
    int getPlayerY();
    int getPlayerAngle();

    World &getWorld();
    Map &getMap();
};

#endif  // __MODELO_LOGIC_H__
