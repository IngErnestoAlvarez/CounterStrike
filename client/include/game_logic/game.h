#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "configuration.h"
#include "map.h"
#include "player.h"
#include "protocolo.h"
#include "team.h"
#include "types.h"
#include "world.h"

class Body;
class Bomb;
class Player;
class Weapon;

class Game {
   private:
    Configuration config;
    World world;
    Map map;

    int final_round = 10;
    int round;
    Phase phase;
    Role winner_team;
    bool has_finished;

    std::vector<Player*> players;
    Team team_a;
    Team team_b;
    Bomb* bomb = nullptr;

    Player *player = nullptr; // eliminar

    void assignBombToRandomPlayer();
    void movePlayerUp(int player_id);
    void movePlayerDown(int player_id);
    void movePlayerLeft(int player_id);
    void movePlayerRight(int player_id);
    void stopPlayer(int player_id);
    void usePlayerWeapon(int player_id);
    void setPlayerAim(int player_id, int x, int y);
    void checkBombState();
    void checkTeamsState();
    void goToNextRound();

   public:
    Game(const std::string &config_filepath,
         const std::string &map_filepath);
    ~Game();

    int addPlayer(TeamID team_id);
    void start();
    void executeCommand(int player_id, Comando command);
    bool hasBombBeenDeactivated();
    bool hasBombExploded();
    Role getWinnerTeam();

    void createBomb(float x, float y);
    void createWeaponDrop(float x, float y, Weapon* weapon);

    World &getWorld();
    Map &getMap();
    const Configuration &getConfig();

    // metodos a eliminar del server
    Player *getPlayer();
    Player *createPlayer(float x, float y);
    void step();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setAim(int x, int y);
    void stopMoving();
    void useWeapon();
    int getX();
    int getY();
    int getAngle();
};

#endif
