#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <syslog.h>

#include <iostream>

#include "app.h"

int main(int argc, char const *argv[]) {
    try {
        App game;
        game.load_media();
        game.main_loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
