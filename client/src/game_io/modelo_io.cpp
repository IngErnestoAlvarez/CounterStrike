#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <utility>

#include "Logger.h"
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
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    bool any_key_pressed = false;
    if (state[SDL_SCANCODE_A]) {
        any_key_pressed = true;
        log->debug("Move Left");
        this->modelo.movePlayerLeft();
    }

    else if (state[SDL_SCANCODE_W]) {
        any_key_pressed = true;
        log->debug("Move Up");
        this->modelo.movePlayerUp();
    }

    else if (state[SDL_SCANCODE_D]) {
        any_key_pressed = true;
        log->debug("Move Right");
        this->modelo.movePlayerRight();
    }

    else if (state[SDL_SCANCODE_S]) {
        any_key_pressed = true;
        log->debug("Move Down");
        this->modelo.movePlayerDown();
    }

    else if (state[SDL_SCANCODE_1]) {
        any_key_pressed = true;
        log->debug("Change to weapon 1");
        this->modelo.changeToW1();
    }

    else if (state[SDL_SCANCODE_2]) {
        any_key_pressed = true;
        log->debug("Change to weapon 2");
        this->modelo.changeToW2();
    }

    else if (state[SDL_SCANCODE_3]) {
        any_key_pressed = true;
        log->debug("Change to weapon 3");
        this->modelo.changeToW3();
    }

    else if (state[SDL_SCANCODE_4]) {
        any_key_pressed = true;
        log->debug("Change to bomb");
        this->modelo.changeToBomb();
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
    this->renderizables.renderFloor(modelo.getStaticIterator(),
                                    modelo.getStaticEnd());
    this->renderizables.renderObjects(modelo.getBodyIterator(),
                                      modelo.getBodyEnd());
    this->renderizables.renderPlayer();
    this->window.render();
}
