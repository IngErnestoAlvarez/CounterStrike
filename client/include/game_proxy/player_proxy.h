#ifndef __PLAYER_PROXY_H__
#define __PLAYER_PROXY_H__

#include <string>

#include "weapon_proxy.h"

class PlayerProxy {
   private:
    WeaponProxy equipped_weapon;
    int life;
    int dinero;
    int posx;
    int posy;
    float angle;
    int time;
    bool gotBomb;

   public:
    PlayerProxy();

    ~PlayerProxy();

    int getX();

    int getY();

    float getAngle();

    int getLife();

    WeaponProxy *getWeapon();

    void setPlayer(char *data, size_t n);
};

#endif
