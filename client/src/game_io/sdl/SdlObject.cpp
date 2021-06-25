#include "game_io/sdl/SdlObject.h"

#include <math.h>

#include <iostream>
#include <utility>

#include "game_io/sdl/SdlImage.h"

SdlObject::SdlObject(std::string const &path, int animation_frames,
                     SdlWindow &window)
    : image(window, path),
      sprite_clips(),
      pos({0, 0}),
      center({16, 32}),
      animation_frames(animation_frames),
      angle(0),
      prevangle(0) {
    sprite_clips->x = 32;
    sprite_clips->y = 32;
    sprite_clips->w = 32;
    sprite_clips->h = 32;
}

SdlObject::SdlObject(SdlObject &&other)
    : image(std::move(other.image)),
      pos(std::move(other.pos)),
      center(std::move(other.pos)),
      animation_frames(other.animation_frames),
      angle(other.angle),
      prevangle(other.prevangle) {
    sprite_clips[0] = std::move(other.sprite_clips[0]);
}

SdlObject::~SdlObject() {}

SdlObject &SdlObject::operator=(SdlObject &&other) {
    if (this == &other) return *this;
    using std::move;
    sprite_clips[0] = other.sprite_clips[0];
    image = move(other.image);
    pos = move(other.pos);
    center = move(other.center);
    angle = other.angle;
    prevangle = other.prevangle;

    return *this;
}

void SdlObject::set_init_pos(int x, int y) {
    this->pos.x = x;
    this->pos.y = y;
}

void SdlObject::set_init_pos(SDL_Point const &pos) {
    this->set_init_pos(pos.x, pos.y);
}

void SdlObject::moveUp() {}

void SdlObject::moveDown() {}

void SdlObject::moveRight() {}

void SdlObject::moveLeft() {}

void SdlObject::render() {
    this->image.render(pos.x, pos.y, angle, center, sprite_clips);
}

void SdlObject::mouse_mov(int x, int y) {}
