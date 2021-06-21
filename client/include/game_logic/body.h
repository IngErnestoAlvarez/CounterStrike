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

    friend class World;

public:
    Body(World* world, float x, float y, float velocity);
    ~Body();
    void setAngle(float angle);
    void startMoving(float x_velocity, float y_velocity);
    void stopMoving();
    void destroy();
    float getX() const;
    float getY() const;
};

#endif