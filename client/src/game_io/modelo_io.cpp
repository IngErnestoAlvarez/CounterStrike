#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cassert>
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
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza check_actions");
    this->check_events();
    this->check_keyboard();
    // this->check_mouse();
    log->debug("Finaliza check_actions");
}

void ModeloIO::check_events() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Chequeando eventos");
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
    log->debug("Terminaron los eventos");
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
        // this->modelo.stopPlayer();
        this->check_mouse();
    }
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    assert(mouseX >= 0);
    assert(mouseY >= 0);
    float angle = atan2(300 - mouseY, 400 - mouseX) + 4.71239; // le sumo 270 grados
    std::cout << "angle in radians: " << angle << std::endl;
    angle = angle * 180 / 3.1416; // se convierte a grados
    this->modelo.setPlayerAngle(angle);

}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::render() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza el seteo de la camara");

    this->window.set_camera_pos(modelo.getPlayerX(), modelo.getPlayerY(),
                                modelo.getWidth() * 32,
                                modelo.getHeight() * 32);

    log->debug("Finaliza el seteo de la camara");
    log->debug("Comienza el render del floor");

    this->renderizables.modifyTexturesIfDead();
    this->renderizables.renderFloor(modelo.getStaticIterator(),
                                    modelo.getStaticEnd());
    this->renderizables.renderObjects(modelo.getBodyIterator(),
                                      modelo.getBodyEnd());
    this->renderizables.renderPlayer();

    log->debug("Finaliza el render del floor");
    log->debug("Comienza el render del window");

    this->window.render();

    log->debug("Finaliza el render del window");
}
