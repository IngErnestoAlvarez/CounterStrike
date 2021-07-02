#ifndef __WEAPONVIEW_H__
#define __WEAPONVIEW_H__

#include "game_io/sdl/SdlObject.h"
#include "game_io/sound/sample.h"
#include "game_logic/weapons/weapon.h"

class WeaponView : public SdlObject {
   private:
    Weapon *weapon;
    Sample sound;

   public:
    WeaponView(std::string const &path, int animation_frames, SdlWindow &window,
               Weapon *weapon);

    ~WeaponView();
    void render(int x, int y, float angle);

    void shoot();
};

#endif  // __WEAPONVIEW_H__
