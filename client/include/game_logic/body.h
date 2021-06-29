#ifndef BODY_H
#define BODY_H

class b2Body;
class World;
class Bullet;
class Player;
class Block;

class Body {
private:
    b2Body* b2_body;
    World& world;
    int id;
    float velocity;
    bool to_be_destroyed;
    void move(float x_velocity, float y_velocity);

    friend class World;

public:
    Body(World& world, float x, float y, float angle, float velocity);
    virtual ~Body();
    void setAngle(float angle);
    void move();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopMoving();
    void destroy();
    virtual void handleCollision(Body* body) = 0;
    virtual void handleCollision(Bullet* bullet) = 0;
    virtual void handleCollision(Player* player) = 0;
    virtual void handleCollision(Block* block) = 0;
    void setToBeDestroyed();
    bool toBeDestroyed() const;
    float getX() const;
    float getY() const;
    float getAngle() const;
};

#endif
