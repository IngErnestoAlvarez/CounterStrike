#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

class Game;
class Player;
class Bullet;
class World;

class Weapon {
protected:
    std::string name;
    Game& game;
    World& world;
    Player& player;
    float damage;
    float precision;
    float range;
    std::vector<Bullet*> active_bullets;

public:
    Weapon(const std::string& name,
           Game& game,
           Player& player);
    virtual void use() = 0;
    ~Weapon();
};

#endif
