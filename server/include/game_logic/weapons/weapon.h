#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <unordered_set>
#include "types.h"

class Game;
class Player;
class Bullet;
class World;

class Weapon {
protected:
    std::string name;
    BodyType type;
    Game& game;
    World& world;
    Player& player;
    float damage;
    float precision;
    float range;
    int ammo;
    std::unordered_set<Bullet*> active_bullets;

public:
    Weapon(const std::string& name,
           BodyType type,
           Game& game,
           Player& player);
    virtual ~Weapon();
    virtual void use() = 0;
    std::string getName() const;
    int getAmmo() const;
    float getRange() const;
    float getDamage(float distance) const;
    void createBullet();
    void createBullet(float angle);
    void deleteInactiveBullets();
    BodyType getType(); 
};

#endif
