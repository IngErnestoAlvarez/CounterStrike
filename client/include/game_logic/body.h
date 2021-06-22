#ifndef BODY_H
#define BODY_H

class b2Body;
class World;

class Body {
private:
    b2Body* b2_body;
    World* world;
    int id;
    float velocity;
    Body(World* world, float x, float y, float velocity);
    void move(float x_velocity, float y_velocity);

    friend class World;

public:
    ~Body();
    void setAngle(float angle);
    void move();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopMoving();
    void destroy();
    float getX() const;
    float getY() const;
};

#endif
