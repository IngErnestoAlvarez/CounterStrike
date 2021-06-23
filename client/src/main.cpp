#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "app.h"

int main(int argc, char const *argv[]) {
    App game;
    game.load_media();
    game.main_loop();

    return 0;
}
