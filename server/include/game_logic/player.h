#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "body.h"

class Block;
class Bomb;
class BombDrop;
class Bullet;
class Game;
class Team;
class Weapon;
class WeaponDrop;

class Player : public Body {
private:
    Game& game;
    Team* team;

    int player_id;
    int team_id;
    int health;
    int money;
    int kill_reward;
    bool has_bomb = false;

    Weapon* default_melee_weapon;
    Weapon* default_range_weapon;
    Weapon* primary_weapon;
    Weapon* equipped_weapon;

public:
    Player(Game& game,
           int player_id,
           int team_id,
           float x,
           float y);

    ~Player();

    int getTeamID() const;
    bool isAlive() const;
    int getHealth() const;
    int getAmmo() const;
    bool isTerrorist() const;

    void useWeapon();
    void takeDamage(float damage);
    void handleEnemyKilled();
    void receiveBomb();
    void activateBomb();
    void addWeapon(Weapon* weapon);
    Weapon* getEquippedWeapon();
    void changeToDMeleeWeapon();
    void changeToDRangeWeapon();
    void registerTeam(Team* team);

    void handleCollision(Body* body) override;
    void handleCollision(Bullet* bullet) override;
    void handleCollision(Player* player) override;
    void handleCollision(Block* block) override;
    void handleCollision(Bomb* bomb) override;
    void handleCollision(WeaponDrop* weapon_drop) override;
    void handleCollision(BombDrop* bomb_drop) override;
};

#endif
