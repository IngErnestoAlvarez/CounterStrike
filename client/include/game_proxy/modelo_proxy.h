#ifndef __MODELO_PROXY_H__
#define __MODELO_PROXY_H__

#include <string>
#include <vector>

#include "body_proxy.h"
#include "player_proxy.h"
#include "protocolo.h"

class ModeloProxy {
   private:
    Protocolo protocolo;
    BodyProxy bodyProxy;

   public:
    ModeloProxy(std::string const &host, std::string const &service);
    ~ModeloProxy();

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();
    void setPlayerAim(int x, int y);
    void stopPlayer();
    void usePlayerWeapon();

    void chargeBodies();

    int getPlayerX();
    int getPlayerY();
    int getPlayerAngle();
};

#endif
