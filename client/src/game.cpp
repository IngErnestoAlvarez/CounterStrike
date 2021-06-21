#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <syslog.h>

#include <iostream>
#include <stdexcept>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlObject.h"

Game::Game() : logic(), view(logic) {}

Game::~Game() {}

void Game::load_media() {
    // ! Terminar esta funcion
}

void Game::main_loop() {
    bool playing = true;
    while (playing) {
        logic.update();
        playing = view.update();
    }
}
