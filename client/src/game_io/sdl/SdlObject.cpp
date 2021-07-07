#include "game_io/sdl/SdlObject.h"

#include <math.h>

#include <iostream>
#include <utility>

#include "game_io/sdl/SdlImage.h"

SdlObject::SdlObject(BodyType type, SdlWindow &window)
    : image(window, type), animation_frames(1) {
    sprite_clips = new SDL_Rect[animation_frames];
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}
SdlObject::SdlObject(std::string const &path, int animation_frames,
                     SdlWindow &window)
    : image(window, path),
      animation_frames(animation_frames),
      center({16, 16}) {
    sprite_clips = new SDL_Rect[animation_frames];
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}

SdlObject::SdlObject(SdlObject &&other)
    : image(std::move(other.image)),
      animation_frames(other.animation_frames),
      center(std::move(other.center)) {
    sprite_clips = other.sprite_clips;
    other.sprite_clips = nullptr;
}

SdlObject::~SdlObject() { delete sprite_clips; }

SdlObject &SdlObject::operator=(SdlObject &&other) {
    if (this == &other) return *this;
    using std::move;
    if (this->sprite_clips != nullptr) delete this->sprite_clips;
    sprite_clips = other.sprite_clips;
    other.sprite_clips = nullptr;
    image = move(other.image);
    center = move(other.center);

    return *this;
}

void SdlObject::render(int posx, int posy, float angle) {
    this->image.render(posx, posy, angle, center, sprite_clips);
}

void SdlObject::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    this->image.setColorMod(r, g, b);
}

void SdlObject::set_alpha(Uint8 a) { this->image.set_alpha(a); }

void SdlObject::blend() { this->image.set_blendMode(SDL_BLENDMODE_BLEND); }
