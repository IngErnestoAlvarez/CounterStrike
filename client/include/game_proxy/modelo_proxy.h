#ifndef __MODELO_PROXY_H__
#define __MODELO_PROXY_H__

#include <vector>

#include "body_proxy.h"
#include "player_proxy.h"

class ModeloProxy {
   private:
   public:
    ModeloProxy();
    ~ModeloProxy();

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();
    void setPlayerAim(int x, int y);
    void stopPlayer();
    void usePlayerWeapon();

    int getPlayerX();
    int getPlayerY();
    int getPlayerAngle();
    PlayerProxy *getPlayer();
    std::vector<BodyProxy *> &getBodies();
};

#endif
