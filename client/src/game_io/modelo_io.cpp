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
      player_view("assets/sprites/ct2.png", 4, this->window),
      life(this->window, "life 100/100"),
      ammo(this->window, "ammo 30/30") {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
    life.set_pos(0, 500);
    ammo.set_pos(550, 500);
}

ModeloIO::ModeloIO()
    : init(),
      window(),
      modelo(nullptr),
      active(true),
      player_view("assets/sprites/ak47.png", 4, this->window),
      life(this->window, "100/100"),
      ammo(this->window, "100/100") {
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
    this->life.render();
    this->ammo.render();
    this->window.render();
}
