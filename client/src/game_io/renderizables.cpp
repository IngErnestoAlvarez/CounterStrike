#include "game_io/renderizables.h"

Renderizables::Renderizables(SdlWindow &window)
    : texts(), objects(), window(&window) {}

Renderizables::~Renderizables() {}

void Renderizables::render() {
    this->renderObjects();
    this->renderTexts();
}

void Renderizables::createTexts() {
    using up = std::unique_ptr<SdlText>;
    this->texts.push_back(up(new SdlText(*this->window, "life 100/100")));
    this->texts.back()->set_pos(0, 500);
    this->texts.push_back(up(new SdlText(*this->window, "ammo 30/30")));
    this->texts.back()->set_pos(550, 500);
}

void Renderizables::createObjects() {
    using up = std::unique_ptr<SdlObject>;
    this->objects.push_back(
        up(new SdlObject("assets/sprites/ct2.png", 4, *this->window)));
}

void Renderizables::renderObjects() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->render();
    }
}

void Renderizables::renderTexts() {
    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i]->render();
    }
}

void Renderizables::moveUp() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->moveUp();
    }
}

void Renderizables::moveDown() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->moveDown();
    }
}

void Renderizables::moveLeft() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->moveLeft();
    }
}

void Renderizables::moveRight() {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->moveRight();
    }
}

void Renderizables::mouseMove(int posX, int posY) {
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->mouse_mov(posX, posY);
    }
}
