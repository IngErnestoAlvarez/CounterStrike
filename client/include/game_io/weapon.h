#ifndef __WEAPONVIEW_H__
#define __WEAPONVIEW_H__

#include "game_io/sdl/SdlObject.h"
#include "game_io/sound/sample.h"
#include "game_proxy/weapon_proxy.h"

class WeaponView : public SdlObject {
   private:
    WeaponProxy *weapon;
    Sample shootSound;
    Sample noBulletSound;

   public:
    WeaponView(std::string const &path, int animation_frames, SdlWindow &window,
               WeaponProxy *weapon);
    WeaponView(BodyType type, int animation_frames, SdlWindow &window,
               WeaponProxy *weapon);

    ~WeaponView();
    void render(int x, int y, float angle);

    void shoot();

    int getAmmo();
};
#endif  // __WEAPONVIEW_H__
