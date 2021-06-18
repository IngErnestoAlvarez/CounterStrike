#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>

#include "game_logic/modelo_logic.h"

#define WIDTH 800
#define HEIGHT 600

ModeloIO::ModeloIO(ModeloLogic &logic)
    : window(WIDTH, HEIGHT), modelo(&logic), active(true) {}

ModeloIO::ModeloIO() : window(WIDTH, HEIGHT), modelo(nullptr), active(true) {}

ModeloIO::~ModeloIO() {}

bool ModeloIO::update() {
    this->check_actions();
    this->window.fill();
    this->window.render();
    return this->active;
}

void ModeloIO::check_actions() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            this->active = false;
        }
    }
}
