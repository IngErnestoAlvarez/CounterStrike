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
      music("assets/music/menu.wav", 50),
      shop(window),
      score(window, modelo.getMyTeam()),
      pauser(200) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
    music.play();
}

ModeloIO::~ModeloIO() {}

bool ModeloIO::update() {
    pauser.update();
    if (pauser.load()) return this->active;
    this->window.clear_renderer();
    // this->check_actions();
    this->window.fill();
    this->renderPhase(modelo.getPhase());
    if (modelo.getRoundState() != NONE) {
        pauser.pause();
    }
    return this->active;
}

void ModeloIO::check_actions() {
    if (pauser.load()) return;
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza check_actions");
    this->check_events();
    this->check_keyboard();
    this->check_mouse();
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

    if (state[SDL_SCANCODE_W]) {
        any_key_pressed = true;
        log->debug("Move Up");
        this->modelo.movePlayerUp();
    }

    if (state[SDL_SCANCODE_D]) {
        any_key_pressed = true;
        log->debug("Move Right");
        this->modelo.movePlayerRight();
    }

    if (state[SDL_SCANCODE_S]) {
        any_key_pressed = true;
        log->debug("Move Down");
        this->modelo.movePlayerDown();
    }

    if (state[SDL_SCANCODE_1]) {
        any_key_pressed = true;
        log->debug("Change to weapon 1");
        this->modelo.changeToW1();
    }

    if (state[SDL_SCANCODE_2]) {
        any_key_pressed = true;
        log->debug("Change to weapon 2");
        this->modelo.changeToW2();
    }

    if (state[SDL_SCANCODE_3]) {
        any_key_pressed = true;
        log->debug("Change to weapon 3");
        this->modelo.changeToW3();
    }

    if (state[SDL_SCANCODE_4]) {
        any_key_pressed = true;
        log->debug("Change to bomb");
        this->modelo.changeToBomb();
    }

    if (!any_key_pressed) {
        this->modelo.stopPlayer();
        // this->check_mouse();
    }
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    assert(mouseX >= 0);
    assert(mouseY >= 0);
    float angle =
        atan2(300 - mouseY, 400 - mouseX) + 4.71239;  // le sumo 270 grados
    std::cout << "angle in radians: " << angle << std::endl;
    angle = angle * 180 / 3.1416;  // se convierte a grados
    this->modelo.setPlayerAngle(angle);
}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::renderPhase(Phase phase) {
    switch (phase) {
        case TEAMS_FORMING_PHASE:
            renderWaiting();
            break;

        case PREPARATION_PHASE:
            renderPreparing();
            break;

        case MAIN_PHASE:
            renderPlaying();
            break;

        default:
            throw std::logic_error(
                "La Phase fue mal invocada en ModeloIO::renderPhase()");
            break;
    }

    this->window.render();
}

void ModeloIO::renderWaiting() {
    SdlText informativeText(this->window, "ESPERANDO A LOS DEMAS JUGADORES",
                            WHITE, 50);
    informativeText.set_pos(50, 300);
    informativeText.render();
}

void ModeloIO::renderPreparing() {
    this->window.set_camera_pos(modelo.getPlayerX(), modelo.getPlayerY(),
                                modelo.getWidth() * 32,
                                modelo.getHeight() * 32);
    modelo.lockStatics();
    this->renderizables.renderFloor(modelo.getStaticIterator(),
                                    modelo.getStaticEnd());
    modelo.unlockStatics();
    modelo.lockBodies();
    this->renderizables.renderObjects(modelo.getBodyIterator(),
                                      modelo.getBodyEnd());
    modelo.unlockBodies();
    this->renderizables.renderPlayer();
    shop.render();
    score.render(modelo.getTeamARounds(), modelo.getTeamBRounds());
}

void ModeloIO::renderPlaying() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza el seteo de la camara");

    this->window.set_camera_pos(modelo.getPlayerX(), modelo.getPlayerY(),
                                modelo.getWidth() * 32,
                                modelo.getHeight() * 32);

    log->debug("Finaliza el seteo de la camara");
    log->debug("Comienza el render del floor");

    this->renderizables.modifyTextures(modelo.getRoundState());
    modelo.lockStatics();
    this->renderizables.renderFloor(modelo.getStaticIterator(),
                                    modelo.getStaticEnd());
    modelo.unlockStatics();
    modelo.lockBodies();
    this->renderizables.renderObjects(modelo.getBodyIterator(),
                                      modelo.getBodyEnd());
    modelo.unlockBodies();
    if (modelo.getRoundState() == 0) {
        log->debug("Entra a renderizar el player");
        this->renderizables.renderPlayer();
    } else if (modelo.getRoundState() == modelo.getMyTeam()) {
        renderizables.renderWin();
    } else {
        renderizables.renderLose();
    }
    score.render(modelo.getTeamARounds(), modelo.getTeamBRounds());

    log->debug("Finaliza el render del floor");
    log->debug("Comienza el render del window");

    log->debug("Finaliza el render del window");
}
