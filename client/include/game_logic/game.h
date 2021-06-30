#ifndef GAME_H
#define GAME_H

#include <string>
#include <unordered_map>

#include "configuration.h"
#include "map.h"
#include "player.h"
#include "world.h"

class Body;

class Game {
   private:
    Configuration config;
    World world;
    Map map;
    Player *player = nullptr;

   public:
    Game(const std::string &config_filepath, const std::string &map_filepath);
    ~Game();
    World &getWorld();
    Map &getMap();
    Player *getPlayer();
    const Configuration &getConfig();
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
