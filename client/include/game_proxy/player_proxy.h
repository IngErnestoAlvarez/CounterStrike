#ifndef __PLAYER_PROXY_H__
#define __PLAYER_PROXY_H__

#include <string>

#include "weapon_proxy.h"

class PlayerProxy {
   private:
    WeaponProxy *equipped_weapon;
    const std::string path2image;

   public:
    PlayerProxy();

    ~PlayerProxy();

    int getX();

    int getY();

    float getAngle();

    const std::string &getPath();
};

#endif
