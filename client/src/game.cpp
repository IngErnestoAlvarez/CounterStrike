#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <syslog.h>

#include <iostream>
#include <stdexcept>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlObject.h"

#define RATE 60

Game::Game() : logic(), view(logic) {}

Game::~Game() {}

void Game::load_media() {
    // ! Terminar esta funcion
}

void Game::main_loop() {
    bool playing = true;
    this->next_time = SDL_GetTicks() + RATE;
    while (playing) {
        logic.update();
        playing = view.update();
        SDL_Delay(this->time_left());
        this->next_time += RATE;
    }
}

Uint32 Game::time_left() {
    Uint32 now = SDL_GetTicks();

    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}
