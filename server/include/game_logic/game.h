#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <unordered_map>

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
class Command;

class Game {
   private:
    Configuration config;
    World world;
    Map map;

    int final_round = 10;
    int round;
    Phase phase;
    TeamID winner_team;
    bool has_finished;

    std::unordered_map<int, Player*> players;
    std::vector<Body*> bodies;

    Team team_a;
    Team team_b;
    Bomb* bomb = nullptr;

    Player *player = nullptr; // eliminar

    void initializeTeams();
    bool canPlayerExecuteCommands(int player_id);
    void movePlayerUp(int player_id);
    void movePlayerDown(int player_id);
    void movePlayerLeft(int player_id);
    void movePlayerRight(int player_id);
    void setPlayerAngle(int player_id, float angle);
    void stopPlayer(int player_id);
    void usePlayerWeapon(int player_id);
    void setWeaponToMelee(int player_id);
    void setWeaponToRange(int player_id);
    void checkBombState();
    void checkTeamsState();
    void goToNextRound();

   public:
    Game(const std::string &config_filepath,
         const std::string &map_filepath);
    ~Game();

    bool isInTeamsFormingPhase();
    bool isRunning();
    bool addPlayer(TeamID team_id, int peer_id);
    void start();
    void executeCommand(Command& command);
    bool hasBombBeenDeactivated();
    bool hasBombExploded();
    TeamID getWinnerTeam();
    std::vector<Body*> getBodies();

    void createBlock(float x, float y);
    void createBomb(float x, float y);
    void createBombDrop(float x, float y);
    void createWeaponDrop(float x, float y, Weapon* weapon);

    World &getWorld();
    Map &getMap();
    const Configuration &getConfig();

    Player* getPlayer(int player_id);

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
