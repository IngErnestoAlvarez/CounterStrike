#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <syslog.h>

#include <stdexcept>

#include "game_io/sdl/SdlImage.h"

Game::Game() : logic(), view(logic) {}

Game::~Game() {}

void Game::load_media() {
    // ! Terminar esta funcion
    SdlImage gun(this->view.getWindow(), "assets/sprites/ct2.png");
    SdlImage terrorist(this->view.getWindow(), "assets/sprites/ak47.png");
}

void Game::main_loop() {
    bool playing = true;
    while (playing) {
        logic.update();
        playing = view.update();
    }
}
