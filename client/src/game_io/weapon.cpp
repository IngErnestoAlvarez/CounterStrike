#include "game_io/weapon.h"

#include <math.h>

#ifndef STRINGIZER
#define STRINGIZER(arg) #arg
#define STR_VALUE(arg) STRINGIZER(arg)
#endif
#ifndef APATH
#define APATH STR_VALUE(ASSETSPATH)
#endif

WeaponView::WeaponView(std::string const &path, int animation_frames,
                       SdlWindow &window, WeaponProxy *weapon)
    : SdlObject(path, 1, window),
      weapon(weapon),
      window(&window),
      prevWeapon(weapon->getBodyType()),
      shootSound(std::string(APATH) + "/sounds/SHOT.wav"),
      noBulletSound(std::string(APATH) + "/sounds/w_empty.wav"),
      ammo(window, weapon->getAmmo()) {
    center = {16, 32};
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
    ammo.set_pos(550, 500);
}

WeaponView::WeaponView(SdlWindow &window, WeaponProxy *weapon)
    : SdlObject(weapon->getBodyType(), window),
      weapon(weapon),
      window(&window),
      prevWeapon(weapon->getBodyType()),
      shootSound(std::string(APATH) + "/sounds/SHOT.wav"),
      noBulletSound(std::string(APATH) + "/sounds/w_empty.wav"),
      ammo(window, weapon->getAmmo()) {
    center = {16, 32};
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
    ammo.set_pos(550, 500);
}
WeaponView::~WeaponView() {}

void WeaponView::render(int x, int y, float angle) {
    checkToChangeWeapon();
    // const int deviation = 8;
    float auxangle = angle + 180.0;
    this->image.render(x, y - 16, auxangle, center, &sprite_clips[0]);
    if (prevWeapon != KNIFE_TYPE) {
        ammo.render(std::to_string(getAmmo()));
    }
}

void WeaponView::shoot() {
    if (weapon->getAmmo() == 0) {
        this->noBulletSound.play();
    } else {
        this->shootSound.play();
    }
}

int WeaponView::getAmmo() { return weapon->getAmmo(); }

void WeaponView::checkToChangeWeapon() {
    if (prevWeapon != weapon->getBodyType()) {
        this->image = SdlImage(*window, weapon->getBodyType());
        prevWeapon = weapon->getBodyType();
    }
}
