#ifndef __WEAPONSHOP_H__
#define __WEAPONSHOP_H__

#include "game_io/sdl/SdlObject.h"
#include "types.h"

class WeaponShop : public SdlObject {
   public:
    WeaponShop(BodyType type, SdlWindow &window);
    ~WeaponShop();
};

#endif  // __WEAPONSHOP_H__
