#include "game_io/weapon.h"

#include <math.h>

WeaponView::WeaponView(std::string const &path, int animation_frames,
                       SdlWindow &window, Weapon *weapon)
    : SdlObject(path, 1, window),
      weapon(weapon),
      sound("assets/sounds/SHOT.wav") {
    center = {16, 32};
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}

WeaponView::~WeaponView() {}

void WeaponView::render(int x, int y, float angle) {
    // const int deviation = 8;
    float auxangle = angle + 180.0;

    // x = int(cos(auxangle / (180.0 / M_PI)) * deviation) + x;
    // y = int(sin(auxangle / (180.0 / M_PI)) * deviation) + y;

    this->image.render(x, y - 16, auxangle, center, &sprite_clips[0]);
}

void WeaponView::shoot() { this->sound.play(); }
