#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <utility>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/text/SdlText.h"
#include "math.h"
#include "syslog.h"

#define WIDTH 800
#define HEIGHT 600

ModeloIO::ModeloIO(ModeloProxy &modelo)
    : init(),
      window(WIDTH, HEIGHT),
      modelo(modelo),
      active(true),
      renderizables(window, modelo.getPlayer()),
      music("assets/music/menu.wav", 50) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
    music.play();
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

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            this->renderizables.shootWeapon();
            this->modelo.usePlayerWeapon();
        }
    }
}

void ModeloIO::check_keyboard() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    bool any_key_pressed = false;
    if (state[SDL_SCANCODE_A]) {
        any_key_pressed = true;
        this->modelo.movePlayerLeft();
    }

    else if (state[SDL_SCANCODE_W]) {
        any_key_pressed = true;
        this->modelo.movePlayerUp();
    }

    else if (state[SDL_SCANCODE_D]) {
        any_key_pressed = true;
        this->modelo.movePlayerRight();
    }

    else if (state[SDL_SCANCODE_S]) {
        any_key_pressed = true;
        this->modelo.movePlayerDown();
    }

    else if (!any_key_pressed) {
        this->modelo.stopPlayer();
    }
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    this->modelo.setPlayerAim(mouseX + window.getCamera().x,
                              mouseY + window.getCamera().y);
}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::render() {
    this->window.set_camera_pos(modelo.getPlayerX(), modelo.getPlayerY(),
                                modelo.getWidth() * 32,
                                modelo.getHeight() * 32);
    this->renderizables.renderObjects(modelo.getBodyIterator(),
                                      modelo.getBodyEnd());
    this->renderizables.renderFloor(modelo.getStaticIterator(),
                                    modelo.getStaticEnd());
    this->window.render();
}
