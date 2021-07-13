#ifndef __SHOPPING_H__
#define __SHOPPING_H__

#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_io/weaponShop.h"

class Shopping {
   private:
    WeaponShop ak47;
    WeaponShop awp;
    WeaponShop m3;
    SdlText akText;
    SdlText awpText;
    SdlText m3Text;
    SdlText bullets;

   public:
    Shopping(SdlWindow &window);

    ~Shopping();

    void render();
};

#endif  // __SHOPPING_H__
