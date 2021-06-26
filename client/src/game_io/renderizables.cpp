#include "game_io/renderizables.h"

#include "game_io/floor.h"
#include "game_io/player.h"
#include "game_logic/player.h"

// Renderizables::Renderizables(SdlWindow &window)
//     : texts(), objects(), window(&window) {
//     createTexts();
//     createObjects();
// }

Renderizables::Renderizables(SdlWindow &window, std::vector<Body *> bodies,
                             Player *player, Map *map)
    : window(&window), map(map) {
    this->createTexts();
    this->createObjects(bodies, player);
    this->createFloor();
}
Renderizables::Renderizables(SdlWindow &window, std::vector<Body *> bodies,
                             Map *map)
    : window(&window), map(map) {
    this->createTexts();
    this->createObjects(bodies);
    this->createFloor();
}

Renderizables::~Renderizables() {}

void Renderizables::render() {
    this->renderObjects();
    this->renderTexts();
}

void Renderizables::createTexts() {
    // using up = std::unique_ptr<SdlText>;
    // this->texts.push_back(up(new SdlText(*this->window, "life 100/100")));
    // this->texts.back()->set_pos(0, 500);
    // this->texts.push_back(up(new SdlText(*this->window, "ammo 30/30")));
    // this->texts.back()->set_pos(550, 500);
}

void Renderizables::createObjects() {
    // using up = std::unique_ptr<SdlObject>;
    // this->objects.push_back(
    //     up(new Floor("assets/sprites/office.png", 1, *this->window)));
    // this->objects.back()->set_init_pos(0, 0);
    // this->objects.push_back(
    //     up(new PlayerView("assets/sprites/ct2.png", 4, *this->window)));
}

void Renderizables::createObjects(std::vector<Body *> bodies, Player *player) {
    // ! Buscar las casillas que entren en la pantalla
}

void Renderizables::createObjects(std::vector<Body *> bodies) {
    // ! Buscar las casillas que entren en la pantalla
}

void Renderizables::createFloor() {
    using up = std::unique_ptr<SdlObject>;
    this->objects.push_back(up(
        new Floor("assets/sprites/office.png", 1, *this->window, this->map)));
    this->objects.push_back(
        up(new SdlObject("assets/sprites/ak47.png", 1, *this->window)));
}

void Renderizables::renderObjects() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->render();
    }
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
