#ifndef __GAME_H__
#define __GAME_H__

#include "game_io/modelo_io.h"
#include "game_logic/modelo_logic.h"

class Game {
   private:
    Uint32 next_time;
    ModeloLogic logic;
    ModeloIO view;

   public:
    Game();

    ~Game();

    void load_media();

    void main_loop();

   private:
    Uint32 time_left();
};

#endif
