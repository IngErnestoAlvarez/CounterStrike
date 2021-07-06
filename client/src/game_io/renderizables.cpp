#include "game_io/renderizables.h"

#include <iostream>
#include <utility>

#include "Logger.h"
#include "game_io/floor.h"
#include "game_io/player.h"
#include "game_io/stencil.h"
#include "types.h"

Renderizables::Renderizables(SdlWindow &window, PlayerProxy *player)
    : window(&window), objects(BodyTypeSize), floor(window) {
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

void Renderizables::createPlayer(PlayerProxy *player) {
    this->player = std::move(
        std::unique_ptr<PlayerView>(new PlayerView(CT2_TYPE, *window, player)));
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
    objects[type] = up(new SdlObject(type, *window));
}

void Renderizables::shootWeapon() { this->player->shootWeapon(); }
