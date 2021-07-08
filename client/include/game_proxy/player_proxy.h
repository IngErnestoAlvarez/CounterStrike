#ifndef __PLAYER_PROXY_H__
#define __PLAYER_PROXY_H__

#include <string>

#include "weapon_proxy.h"

class PlayerProxy {
   private:
    BodyType type;
    WeaponProxy equipped_weapon;
    int life;
    int money;
    int posx;
    int posy;
    float angle;
    int time;
    bool gotBomb;

   public:
    PlayerProxy(BodyType type);

    ~PlayerProxy();

    int getX();

    int getY();

    float getAngle();

    int getLife();

    BodyType getType();

    WeaponProxy *getWeapon();

    void setPlayer(char *data, size_t n);

    int getTime() const { return time; }

    bool getGotBomb() const { return gotBomb; }

    int getMoney() const { return money; }
};

#endif
