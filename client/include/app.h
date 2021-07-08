#ifndef __APP_H__
#define __APP_H__

#include <string>

#include "game_io/modelo_io.h"
#include "game_proxy/modelo_proxy.h"

class App {
   private:
    Uint32 next_time;
    ModeloProxy proxy;
    ModeloIO view;

   public:
    App(std::string const &host, std::string const &service,
        const char *teamID);

    ~App();

    void load_media();

    void main_loop();

   private:
    Uint32 time_left();
};

#endif
