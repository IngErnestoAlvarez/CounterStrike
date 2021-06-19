#ifndef __GAME_H__
#define __GAME_H__

#include "game_io/modelo_io.h"
#include "game_logic/modelo_logic.h"

class Game {
   private:
    ModeloLogic logic;
    ModeloIO view;

   public:
    Game();

    ~Game();

    void load_media();

    void main_loop();
};

#endif
