#include "game_io/renderizables.h"

Renderizables::Renderizables(SdlWindow &window)
    : images(), texts(), objects(), window(&window) {}

Renderizables::~Renderizables() {}

void Renderizables::render() {
    this->renderImages();
    this->renderObjects();
    this->renderTexts();
}

void Renderizables::createImages() {}

void Renderizables::createTexts() {
    SdlText life(*this->window, "life 100/100");
    SdlText ammo(*this->window, "ammo 30/30");
    this->texts.push_back(*this->window, "life 100/100");
}
