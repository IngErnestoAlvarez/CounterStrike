#include "game_io/modelo_io.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <utility>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_logic/cell.h"
#include "game_logic/modelo_logic.h"
#include "math.h"
#include "syslog.h"

#define WIDTH 800
#define HEIGHT 600

ModeloIO::ModeloIO(ModeloLogic &logic)
    : init(),
      window(WIDTH, HEIGHT),
      modelo(logic),
      active(true),
      renderizables(window, logic.getBodies(), logic.getPlayer()) {
    SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
}

// ModeloIO::ModeloIO()
//     : init(), window(), modelo(nullptr), active(true), renderizables(window)
//     { SDL_SetRenderDrawColor(window.getRendered(), 0xFF, 0xFF, 0xFF, 0xFF);
// }

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
    bool any_key_pressed = false;
    if (state[SDL_SCANCODE_A]) {
        any_key_pressed = true;
        this->modelo.movePlayerLeft();
    }

    if (state[SDL_SCANCODE_W]) {
        any_key_pressed = true;
        this->modelo.movePlayerUp();
    }

    if (state[SDL_SCANCODE_D]) {
        any_key_pressed = true;
        this->modelo.movePlayerRight();
    }

    if (state[SDL_SCANCODE_S]) {
        any_key_pressed = true;
        this->modelo.movePlayerDown();
    }

    if (!any_key_pressed) {
        this->modelo.stopPlayer();
    }
}

void ModeloIO::check_mouse() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    this->modelo.setPlayerAim(mouseX, mouseY);
}

SdlWindow &ModeloIO::getWindow() { return this->window; }

void ModeloIO::clearRenderer() { this->window.clear_renderer(); }

void ModeloIO::render() {
    // this->renderizables.render();
    // this->window.render();

    SDL_Renderer *renderer = this->window.getRendered();
    SDL_Rect dst;
    SDL_RendererFlip flip =
        SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

    SDL_Texture *player =
        IMG_LoadTexture(renderer, "../assets/sprites/player.png");
    SDL_Texture *wall = IMG_LoadTexture(renderer, "../assets/sprites/wall.png");
    // SDL_Texture* ground = IMG_LoadTexture(renderer,
    // "../assets/sprites/office.png");

    for (Cell &cell : modelo.getMap()) {
        dst = {int(cell.getWorldX()) - 4, int(cell.getWorldY()), 32, 32};
        if (cell.canBeAccesed()) {
            // SDL_RenderCopy(renderer, ground, nullptr, &dst);
        } else {
            SDL_RenderCopy(renderer, wall, nullptr, &dst);
        }
    }

    dst = {modelo.getPlayerX(), modelo.getPlayerY(), 32, 32};
    SDL_RenderCopyEx(renderer, player, nullptr, &dst, modelo.getPlayerAngle(),
                     nullptr, flip);
    SDL_RenderPresent(renderer);
}
