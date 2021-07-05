#ifndef __WEAPON_PROXY_H__
#define __WEAPON_PROXY_H__

#include <string>

#include "types.h"

class WeaponProxy {
   private:
    BodyType weapon;
    int ammo;
    int maxammo;

   public:
    WeaponProxy();

    ~WeaponProxy();

    int getAmmo();

    int getMaxAmmo();

    void setAmmo(int ammo);

    void setWeapon(int weapon);
};

#endif
