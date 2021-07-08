#include "game_io/renderizables.h"

#include <iostream>
#include <utility>

#include "Logger.h"
#include "game_io/floor.h"
#include "game_io/player.h"
#include "game_io/stencil.h"
#include "types.h"

Renderizables::Renderizables(SdlWindow &window, PlayerProxy *player)
    : window(&window),
      objects(BodyTypeSize),
      floor(window),
      roundsRender(window) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza el constructor de renderizables");
    createPlayer(player);
    log->debug("Finaliza el constructor de renderizables");
}
Renderizables::~Renderizables() {}

void Renderizables::renderObjects(bodyVector::iterator it,
                                  bodyVector::iterator end) {
    for (; it != end; it++) {
        if (objects[it->tipo].get() == nullptr) {
            createObject(it->tipo);
        }
        objects[it->tipo]->render(it->posx, it->posy, it->angle);
    }
}

void Renderizables::renderFloor(bodyVector::iterator it,
                                bodyVector::iterator end) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    floor.render();
    for (; it != end; it++) {
        if (objects[it->tipo].get() == nullptr) {
            createObject(it->tipo);
        }
        objects[it->tipo]->render(it->posx, it->posy, 0);
    }
}

void Renderizables::renderPlayer() { player->render(); }

void Renderizables::renderWin() {
    camFilter(50, 50, 50);
    roundsRender.renderWin();
}

void Renderizables::renderLose() {
    camFilter(50, 50, 50);
    roundsRender.renderLose();
}

void Renderizables::createPlayer(PlayerProxy *player) {
    this->player =
        std::move(std::unique_ptr<PlayerView>(new PlayerView(*window, player)));
}

void Renderizables::createStatics(bodyVector::iterator it,
                                  bodyVector::iterator end) {
    for (; it != end; it++) {
        if (objects[it->tipo].get() == nullptr) {
            createObject(it->tipo);
        }
    }
}

void Renderizables::createObject(BodyType type) {
    using up = std::unique_ptr<SdlObject>;
    if (objects[type].get() == nullptr) {
        objects[type] = up(new SdlObject(type, *window));
    }
}

void Renderizables::camFilter(Uint8 r, Uint8 g, Uint8 b) {
    for (auto &object : objects) {
        if (object.get() != nullptr) {
            object->setColorMod(r, g, b);
        }
    }
    this->player->setColorMod(r, g, b);
    this->floor.setColorMod(r, g, b);
}

void Renderizables::shootWeapon() { this->player->shootWeapon(); }

void Renderizables::modifyTextures(uint8_t roundState) {
    const SDL_Color aliveColors{255, 255, 255, 255};
    const SDL_Color deadColors{60, 50, 50, 255};
    if (roundState != 0) {
        camFilter(deadColors.r, deadColors.g, deadColors.b);
        return;
    }
    if (this->player->isDead()) {
        camFilter(deadColors.r, deadColors.g, deadColors.b);
        return;
    }
    camFilter(aliveColors.r, aliveColors.g, aliveColors.b);
}
