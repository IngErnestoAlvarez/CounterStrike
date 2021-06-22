#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>
#include "map.h"
#include "configuration.h"
#include "player.h"
#include "world.h"

class Game {
private:
    Configuration config;
    World world;
    Map map;
    // std::unordered_map<int, Player> players;
    // std::unordered_map<int, Item> items;

public:
    Game(const std::string& config_filepath, const std::string& map_filepath);
    ~Game();
    // void moveUp(int player_id);
    // void moveDown(int player_id);
    // void moveLeft(int player_id);
    // void moveRight(int player_id);
    World& getWorld();
    Map& getMap();
    const Configuration& getConfig();
};

#endif
