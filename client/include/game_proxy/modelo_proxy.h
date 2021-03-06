#ifndef __MODELO_PROXY_H__
#define __MODELO_PROXY_H__

#include <atomic>
#include <mutex>
#include <string>
#include <vector>

#include "body_proxy.h"
#include "game_io/pauser.h"
#include "game_proxy/final_scores.h"
#include "player_proxy.h"
#include "protocolo.h"
#include "types.h"

class ModeloProxy {
   private:
    TeamID myTeam;
    Protocolo protocolo;
    BodyProxy bodyProxy;
    BodyProxy staticsProxy;
    PlayerProxy player;
    TeamID roundResult;
    Phase phase;
    uint8_t teamAWins;
    uint8_t teamBWins;
    socket_t skt;
    std::mutex mutex;
    FinalScores finalScores;
    std::atomic_bool active;
    Pauser pauser;

   public:
    ModeloProxy(std::string const &host, std::string const &service,
                std::string const &game_id, const char *teamID);
    ~ModeloProxy();

    bool isActive();
    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();
    void setPlayerAngle(float angle);
    void stopPlayer();
    void usePlayerWeapon();
    void changeToW1();
    void changeToW2();
    void changeToW3();
    void changeToBomb();

    bodyVector::iterator getBodyIterator();
    bodyVector::iterator getBodyEnd();
    void lockBodies();
    void unlockBodies();

    bodyVector::iterator getStaticIterator();
    bodyVector::iterator getStaticEnd();
    void lockStatics();
    void unlockStatics();

    int getPlayerX();
    int getPlayerY();
    float getPlayerAngle();
    PlayerProxy *getPlayer();

    void initialize();

    void update();

    void close();

    void finally();

    int getWidth();
    int getHeight();

    TeamID getRoundState();
    TeamID getMyTeam();

    uint8_t getTeamARounds();
    uint8_t getTeamBRounds();

    FinalScores *getFinalScores();

    Phase getPhase();

    void deactivate();

    bool isPaused();

   private:
    void chargeBodies();
    void chargePlayer();
    void chargeStatics();
};

#endif
