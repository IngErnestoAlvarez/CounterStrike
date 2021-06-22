#include "game_io/sdl/SdlObject.h"

#include <math.h>

#include <iostream>

#include "game_io/sdl/SdlImage.h"

SdlObject::SdlObject(std::string const &path, int animation_frames,
                     SdlWindow &window)
    : image(window, path),
      sprite_clips(),
      x_pos(0),
      y_pos(0),
      center({16, 16}),
      animation_frames(4),
      angle(0),
      prevangle(0) {
    sprite_clips->x = 32;
    sprite_clips->y = 32;
    sprite_clips->w = 32;
    sprite_clips->h = 32;
}

SdlObject::~SdlObject() {}

void SdlObject::set_init_pos(int x, int y) {
    this->x_pos = x;
    this->y_pos = y;
}

void SdlObject::moveUp() { y_pos -= this->sprite_clips->h / 16; }

void SdlObject::moveDown() { y_pos += this->sprite_clips->h / 16; }

void SdlObject::moveRight() { x_pos += this->sprite_clips->h / 16; }

void SdlObject::moveLeft() { x_pos -= this->sprite_clips->h / 16; }

void SdlObject::render(SdlWindow &window) {
    this->image.render(x_pos, y_pos, angle, center, sprite_clips);
}

void SdlObject::mouse_mov(int x, int y) {
    this->prevangle = this->angle;
    this->angle = (atan2(y_pos - y, x_pos - x) * 180.0000 / M_PI) - 90;
    if (!angle) {
        this->angle = this->prevangle;
    }
    return;
}
