#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Weapon;
class Game;

class Player {
private:
    int x;
    int y;
    Game& game;
    std::vector<Weapon*> inventory;
    void move(int x_target, int y_target);

public:
    Player(Game& game, int x, int y);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void addWeaponToInventory(int weapon_id);


    int getX() const;
    int getY() const;
};

#endif
