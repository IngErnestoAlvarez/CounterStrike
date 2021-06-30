#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "body.h"

class Weapon;
class Game;
class Bullet;
class Block;

class Player : public Body {
private:
    int team_id;
    int health;
    int money;
    int kill_reward;
    Weapon* default_melee_weapon;
    Weapon* default_range_weapon;
    Weapon* primary_weapon;
    Weapon* equipped_weapon;

public:
    Player(Game& game, int team_id, float x, float y);
    void addWeaponToInventory(Weapon* weapon);
    Weapon* getEquippedWeapon();
    int getTeamID() const;
    bool isAlive() const;
    int getHealth() const;
    int getAmmo() const;
    void useWeapon();
    void takeDamage(float damage);
    void handleEnemyKilled();
    void handleCollision(Body* body) override;
    void handleCollision(Bullet* bullet) override;
    void handleCollision(Player* player) override;
    void handleCollision(Block* block) override;
};

#endif
