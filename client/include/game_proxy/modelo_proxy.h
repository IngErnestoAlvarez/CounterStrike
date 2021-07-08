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
    uint8_t roundResult;
    socket_t skt;

   public:
    ModeloProxy(std::string const &host, std::string const &service,
                const char *teamID);
    ~ModeloProxy();

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();
    void setPlayerAim(int x, int y);
    void setPlayerAngle(float angle);
    void stopPlayer();
    void usePlayerWeapon();
    void changeToW1();
    void changeToW2();
    void changeToW3();
    void changeToBomb();

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

    uint8_t getRoundState();

   private:
    void chargeBodies();
    void chargePlayer();
    void chargeStatics();
};

#endif
