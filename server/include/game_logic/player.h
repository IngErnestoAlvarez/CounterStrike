#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "types.h"
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
    int ammo;
    int kill_reward;
    bool has_bomb = false;
    int kills;
    int deaths;
    int earned_money;

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
    int getKills() const;
    int getDeaths() const;
    int getMoney() const;
    int getEarnedMoney() const;

    void useWeapon();
    void takeDamage(float damage);
    void handleEnemyKilled();
    void receiveBomb();
    void activateBomb();
    bool hasBomb();
    void addWeapon(Weapon* weapon);
    Weapon* getEquippedWeapon();
    BodyType getEquippedWeaponType();
    void changeToPrimaryWeapon();
    void changeToDMeleeWeapon();
    void changeToDRangeWeapon();
    void reset();
    void registerTeam(Team* team);
    void setRole(Role role);
    void buyAK47();
    void buyAWP();
    void buyM3();
    void buyWeapon(BodyType type);
    void buyBullets();
    void useAmmo();

    void handleCollision(Body* body) override;
    void handleCollision(Bullet* bullet) override;
    void handleCollision(Player* player) override;
    void handleCollision(Block* block) override;
    void handleCollision(Bomb* bomb) override;
    void handleCollision(WeaponDrop* weapon_drop) override;
    void handleCollision(BombDrop* bomb_drop) override;
};

#endif
