#include "game_io/stencil.h"

Stencil::Stencil(SdlWindow &window)
    : SdlObject("assets/sprites/stencil.png", 1, window) {
    this->pos = {0, 0};
    this->blend();
    this->set_alpha(100);
    this->center = {800, 600};
    this->sprite_clips->h = 1200;
    this->sprite_clips->w = 1600;
    this->sprite_clips->x = 0;
    this->sprite_clips->y = 0;
}

Stencil::~Stencil() {}

void Stencil::render(int x, int y, float angle) {
    this->image.render(x - 784, y - 584, angle + 90, center, sprite_clips);
}
