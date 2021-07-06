#include "game_io/weapon.h"

#include <math.h>

#include "Logger.h"

WeaponView::WeaponView(std::string const &path, int animation_frames,
                       SdlWindow &window, WeaponProxy *weapon)
    : SdlObject(path, 1, window),
      weapon(weapon),
      shootSound("assets/sounds/SHOT.wav"),
      noBulletSound("assets/sounds/w_empty.wav") {
    center = {16, 32};
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
}

WeaponView::WeaponView(BodyType type, int animation_frames, SdlWindow &window,
                       WeaponProxy *weapon)
    : SdlObject(type, window),
      weapon(weapon),
      shootSound("assets/sounds/SHOT.wav"),
      noBulletSound("assets/sounds/w_empty.wav") {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza WeaponView constructor");
    center = {16, 32};
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 32;
    sprite_clips[0].h = 32;
    log->debug("Finaliza WeaponView constructor");
}
WeaponView::~WeaponView() {}

void WeaponView::render(int x, int y, float angle) {
    // const int deviation = 8;
    float auxangle = angle + 180.0;

    // x = int(cos(auxangle / (180.0 / M_PI)) * deviation) + x;
    // y = int(sin(auxangle / (180.0 / M_PI)) * deviation) + y;

    this->image.render(x, y - 16, auxangle, center, &sprite_clips[0]);
}

void WeaponView::shoot() {
    if (weapon->getAmmo() == 0) {
        this->noBulletSound.play();
    } else {
        this->shootSound.play();
    }
}

int WeaponView::getAmmo() { return weapon->getAmmo(); }
