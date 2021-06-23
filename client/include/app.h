#ifndef __APP_H__
#define __APP_H__

#include "game_io/modelo_io.h"
#include "game_logic/modelo_logic.h"

class App {
   private:
    Uint32 next_time;
    ModeloLogic logic;
    ModeloIO view;

   public:
    App();

    ~App();

    void load_media();

    void main_loop();

   private:
    Uint32 time_left();
};

#endif
