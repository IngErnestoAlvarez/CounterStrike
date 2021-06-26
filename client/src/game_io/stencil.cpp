#include "game_io/stencil.h"

Stencil::Stencil(SdlWindow &window)
    : SdlObject("assets/sprites/stencil.png", 1, window) {
    this->blend();
    this->set_alpha(100);
    this->center = {400, 300};
    this->sprite_clips->h = 600;
    this->sprite_clips->w = 800;
    this->sprite_clips->x = 0;
    this->sprite_clips->y = 0;
}

Stencil::~Stencil() {}
