#include "game_io/stencil.h"

#include "Logger.h"

Stencil::Stencil(SdlWindow &window)
    : SdlObject("assets/sprites/stencil.png", 1, window) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza constructor Stencil");
    this->blend();
    this->set_alpha(100);
    this->center = {800, 600};
    this->sprite_clips->h = 1200;
    this->sprite_clips->w = 1600;
    this->sprite_clips->x = 0;
    this->sprite_clips->y = 0;
    log->debug("Finaliza constructor Stencil");
}

Stencil::~Stencil() {}

void Stencil::render(int x, int y, float angle) {
    this->image.render(x - 784, y - 584, angle + 90, center, sprite_clips);
}
