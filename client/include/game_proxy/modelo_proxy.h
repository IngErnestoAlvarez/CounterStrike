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
    BodyProxy staticsProxy;
    PlayerProxy player;
    socket_t skt;

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

    bodyVector::iterator getBodyIterator();
    bodyVector::iterator getBodyEnd();

    bodyVector::iterator getStaticIterator();
    bodyVector::iterator getStaticEnd();

    int getPlayerX();
    int getPlayerY();
    float getPlayerAngle();
    PlayerProxy *getPlayer();

    void initialize();

    void update();

    int getWidth();
    int getHeight();

   private:
    void chargeBodies();
    void chargePlayer();
    void chargeStatics();
};

#endif
