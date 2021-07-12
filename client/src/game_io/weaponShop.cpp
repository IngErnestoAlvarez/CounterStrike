#include "game_io/weaponShop.h"

WeaponShop::WeaponShop(BodyType type, SdlWindow &window)
    : SdlObject(type, window) {
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 51;
    sprite_clips[0].h = 17;
    center = {25, 8};
}

WeaponShop::~WeaponShop() {}
