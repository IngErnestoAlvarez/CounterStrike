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
    Body *player = nullptr;

   public:
    Game(const std::string &config_filepath, const std::string &map_filepath);
    ~Game();
    World &getWorld();
    Map &getMap();
    Player *getPlayer();
    const Configuration &getConfig();
    Body *createPlayer(float x, float y);
    void step();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setAim(int x, int y);
    void stopMoving();

    int getX();
    int getY();
    int getAngle();
};

#endif
