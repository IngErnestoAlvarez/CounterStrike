#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdexcept>

#include "game_logic/modelo_logic.h"
#include "syslog.h"

#define WIDTH 800
#define HEIGHT 600

ModeloIO::ModeloIO(ModeloLogic &logic)
    : window(), modelo(&logic), active(true) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize!");
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        syslog(LOG_WARNING, "Linear texture filtering not enabled!");
    }

    window = SdlWindow(WIDTH, HEIGHT);

    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Quit();
        throw std::runtime_error("SDL_image could not initialize!");
    }
}

ModeloIO::ModeloIO() : window(), modelo(nullptr), active(true) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize!");
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        syslog(LOG_WARNING, "Linear texture filtering not enabled!");
    }

    window = SdlWindow(WIDTH, HEIGHT);

    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Quit();
        throw std::runtime_error("SDL_image could not initialize!");
    }
}

ModeloIO::~ModeloIO() {
    IMG_Quit();
    SDL_Quit();
}

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

SdlWindow &ModeloIO::getWindow() { return this->window; }
