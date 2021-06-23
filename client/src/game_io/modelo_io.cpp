#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <utility>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/text/SdlText.h"
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
      renderizables(window) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
}

ModeloIO::ModeloIO()
    : init(), window(), modelo(nullptr), active(true), renderizables(window) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
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
    if (state[SDL_SCANCODE_A]) this->renderizables.moveLeft();
    if (state[SDL_SCANCODE_W]) this->renderizables.moveUp();
    if (state[SDL_SCANCODE_D]) this->renderizables.moveRight();
    if (state[SDL_SCANCODE_S]) this->renderizables.moveDown();
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    this->renderizables.mouseMove(mouseX, mouseY);
}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::render() {
    this->renderizables.render();
    this->window.render();
}
