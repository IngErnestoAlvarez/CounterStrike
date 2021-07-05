#ifndef BODY_H
#define BODY_H

#include "types.h"

class b2Body;
class Block;
class Bomb;
class BombDrop;
class Bullet;
class Player;
class WeaponDrop;
class World;

class Body {
private:
    b2Body* b2_body;
    World& world;
    BodyType type;
    float velocity;
    bool to_be_destroyed;
    void move(float x_velocity, float y_velocity);

    friend class World;

public:
    Body(World& world,
         BodyType type,
         float x,
         float y,
         float angle,
         float velocity);

    virtual ~Body();

    void move();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopMoving();
    void setAngle(float angle);
    void destroy();
    void setToBeDestroyed();

    BodyType getType() const;
    float getX() const;
    float getY() const;
    float getAngle() const;
    bool isDestroyed() const;
    bool toBeDestroyed() const;

    virtual void update();

    virtual void handleCollision(Body* body) = 0;
    virtual void handleCollision(Bullet* bullet) = 0;
    virtual void handleCollision(Player* player) = 0;
    virtual void handleCollision(Block* block) = 0;
    virtual void handleCollision(Bomb* bomb) = 0;
    virtual void handleCollision(WeaponDrop* weapon_drop) = 0;
    virtual void handleCollision(BombDrop* bomb_drop) = 0;
};

#endif
