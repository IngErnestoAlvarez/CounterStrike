#include "game_io/stencil.h"

Stencil::Stencil(SdlWindow &window)
    : SdlObject("assets/sprites/stencil.png", 1, window) {
    this->pos = {0, 0};
    this->blend();
    this->set_alpha(100);
    this->center = {400, 300};
    this->sprite_clips->h = 600;
    this->sprite_clips->w = 800;
    this->sprite_clips->x = 0;
    this->sprite_clips->y = 0;
}

Stencil::~Stencil() {}

void Stencil::mouse_mov(int x, int y) {
    this->prevangle = this->angle;
    this->angle = (atan2(center.y - y, center.x - x) * 180.0000 / M_PI) - 90;
    if (!angle) {
        this->angle = this->prevangle;
    }
}
