#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <unordered_set>

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
    int ammo;
    std::unordered_set<Bullet*> active_bullets;

public:
    Weapon(const std::string& name,
           Game& game,
           Player& player);
    virtual void use() = 0;
    std::string getName() const;
    int getAmmo() const;
    float getRange() const;
    void createBullet();
    void createBullet(float angle);
    void deleteInactiveBullets();
    ~Weapon();
};

#endif
