#include "game_io/renderizables.h"

#include <iostream>

#include "game_io/floor.h"
#include "game_io/player.h"
#include "game_io/stencil.h"
#include "game_logic/player.h"
// Renderizables::Renderizables(SdlWindow &window)
//     : texts(), objects(), window(&window) {
//     createTexts();
//     createObjects();
// }

Renderizables::Renderizables(SdlWindow &window, std::vector<Body *> bodies,
                             Player *player, Map *map)
    : window(&window), map(map) {
    this->createFloor();
    this->createObjects(bodies, player);
    this->createTexts();
}
Renderizables::~Renderizables() {}

void Renderizables::render() {
    this->renderObjects();
    this->renderTexts();
}

void Renderizables::createTexts() {}

void Renderizables::createObjects() {
    // using up = std::unique_ptr<SdlObject>;
    // this->objects.push_back(
    //     up(new Floor("assets/sprites/office.png", 1, *this->window)));
    // this->objects.back()->set_init_pos(0, 0);
    // this->objects.push_back(
    //     up(new PlayerView("assets/sprites/ct2.png", 4, *this->window)));
}

void Renderizables::createObjects(std::vector<Body *> bodies, Player *player) {
    using up = std::unique_ptr<SdlObject>;
    this->player = std::unique_ptr<PlayerView>(
        new PlayerView("assets/sprites/ct2.png", 3, *window, player));
    this->objects.push_back(
        up(new SdlObject("assets/sprites/ak47.png", 1, *window)));
    this->objects.back()->set_init_pos(300, 200);
}

void Renderizables::createFloor() {
    using up = std::unique_ptr<SdlObject>;
    this->objects.push_back(up(
        new Floor("assets/sprites/office.png", 1, *this->window, this->map)));
}

void Renderizables::renderObjects() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->render();
    }
    std::cout << "antes player" << std::endl;
    this->player->render();
}

void Renderizables::renderTexts() {
    for (size_t i = 0; i < texts.size(); i++) {
        texts[i]->render();
    }
}

void Renderizables::renderFloor() {}

// void Renderizables::moveUp() {
//     for (size_t i = 0; i < objects.size(); i++) {
//         objects[i]->moveUp();
//     }
// }

// void Renderizables::moveDown() {
//     for (size_t i = 0; i < objects.size(); i++) {
//         objects[i]->moveDown();
//     }
// }

// void Renderizables::moveLeft() {
//     for (size_t i = 0; i < objects.size(); i++) {
//         objects[i]->moveLeft();
//     }
// }

// void Renderizables::moveRight() {
//     for (size_t i = 0; i < objects.size(); i++) {
//         objects[i]->moveRight();
//     }
// }

void Renderizables::mouseMove(int posX, int posY) {
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i]->mouse_mov(posX, posY);
    }
}

void Renderizables::shootWeapon() { this->player->shootWeapon(); }
