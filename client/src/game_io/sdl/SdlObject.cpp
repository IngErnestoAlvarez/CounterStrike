#include "game_io/sdl/SdlObject.h"

#include <math.h>

#include <iostream>
#include <utility>

#include "game_io/sdl/SdlImage.h"

SdlObject::SdlObject(std::string const &path, int animation_frames,
                     SdlWindow &window)
    : image(window, path),
      animation_frames(animation_frames),
      pos({0, 0}),
      center({16, 16}),
      angle(0),
      prevangle(0),
      body(nullptr) {
    sprite_clips = new SDL_Rect[animation_frames];
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}

SdlObject::SdlObject(std::string const &path, int animation_frames,
                     SdlWindow &window, Body *body)
    : image(window, path),
      animation_frames(animation_frames),
      pos({0, 0}),
      center({16, 16}),
      angle(0),
      prevangle(0),
      body(body) {
    sprite_clips = new SDL_Rect[animation_frames];
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}

SdlObject::SdlObject(SdlObject &&other)
    : image(std::move(other.image)),
      animation_frames(other.animation_frames),
      pos(std::move(other.pos)),
      center(std::move(other.pos)),
      angle(other.angle),
      prevangle(other.prevangle) {
    sprite_clips = other.sprite_clips;
    other.sprite_clips = nullptr;
}

SdlObject::~SdlObject() { delete sprite_clips; }

SdlObject &SdlObject::operator=(SdlObject &&other) {
    if (this == &other) return *this;
    using std::move;
    sprite_clips = other.sprite_clips;
    other.sprite_clips = nullptr;
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

// void SdlObject::moveUp() {}

// void SdlObject::moveDown() {}

// void SdlObject::moveRight() {}

// void SdlObject::moveLeft() {}

void SdlObject::render() {
    this->image.render(pos.x, pos.y, angle, center, sprite_clips);
}

void SdlObject::mouse_mov(int x, int y) {}

void SdlObject::set_alpha(Uint8 a) { this->image.set_alpha(a); }

void SdlObject::blend() { this->image.set_blendMode(SDL_BLENDMODE_BLEND); }
