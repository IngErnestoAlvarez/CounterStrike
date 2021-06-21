#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <utility>

#include "game_io/sdl/SdlImage.h"
#include "game_logic/modelo_logic.h"
#include "math.h"
#include "syslog.h"

#define WIDTH 800
#define HEIGHT 600

ModeloIO::ModeloIO(ModeloLogic &logic)
    : init(),
      window(WIDTH, HEIGHT),
      modelo(&logic),
      active(true),
      player_view("assets/sprites/ct2.png", 4, this->window) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
}

ModeloIO::ModeloIO()
    : init(),
      window(),
      modelo(nullptr),
      active(true),
      player_view("assets/sprites/ak47.png", 4, this->window) {
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

ModeloIO::~ModeloIO() {}

bool ModeloIO::update() {
    this->window.clear_renderer();
    this->check_actions();
    this->window.fill();
    this->render();
    return this->active;
}

void ModeloIO::check_actions() {
    this->check_events();
    this->check_keyboard();
    this->check_mouse();
}

void ModeloIO::check_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            this->active = false;
        }
    }
}

void ModeloIO::check_keyboard() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A]) this->player_view.moveLeft();
    if (state[SDL_SCANCODE_W]) this->player_view.moveUp();
    if (state[SDL_SCANCODE_D]) this->player_view.moveRight();
    if (state[SDL_SCANCODE_S]) this->player_view.moveDown();
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    this->player_view.mouse_mov(mouseX, mouseY);
}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::render() {
    this->player_view.render(window);
    this->window.render();
}
