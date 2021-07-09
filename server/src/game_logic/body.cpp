#include <iostream>
#include <cmath>

#include "game_logic/body.h"
#include "game_logic/world.h"

Body::Body(World& world,
           BodyType type,
           float x,
           float y,
           float angle,
           float velocity)
    : world(world),
      id(world.bodies.size()),
      type(type),
      velocity(velocity),
      to_be_destroyed(false),
      x(x),
      y(y),
      angle(angle),
      initial_x(x),
      initial_y(y) {
    this->initializeBody();
    this->world.bodies.push_back(this);
}

Body::~Body() {
    if (!this->isDestroyed()) {
        this->world.bodies[this->id] = nullptr;
        this->destroy();
    }
}

void Body::initializeBody() {
    b2_body_def.position.Set(initial_x, initial_y);
    b2_body_def.angle = angle;
    b2_body_def.type = velocity > 0 ? b2_dynamicBody : b2_staticBody;
    b2_body_def.allowSleep = velocity > 0;
    b2_body_def.fixedRotation = true;
    b2_body_def.userData = this;
    this->b2_body = this->world.b2_world->CreateBody(&b2_body_def);
    b2_polygon_shape.SetAsBox(10, 10);
    this->b2_body->CreateFixture(&b2_polygon_shape, 1);
}

int Body::getID() const {
    return this->id;
}

BodyType Body::getType() const {
    return this->type;
}

void Body::setType(BodyType type) {
    this->type = type;
}

void Body::setAngle(float angle) {
    this->b2_body->SetTransform(this->b2_body->GetPosition(), angle);
}

void Body::move(float x_velocity, float y_velocity) {
    this->b2_body->SetLinearVelocity(b2Vec2(x_velocity, y_velocity));
}

void Body::move() {
    float angle = this->getAngle();
    float x_velocity = std::cos(angle) * this->velocity;
    float y_velocity = std::sin(angle) * this->velocity;
    this->move(x_velocity, y_velocity);
}

void Body::moveLeft() {
    this->move(-this->velocity, 0);
}

void Body::moveRight() {
    this->move(this->velocity, 0);
}

void Body::moveUp() {
    this->move(0, -this->velocity);
}

void Body::moveDown() {
    this->move(0, this->velocity);
}

void Body::stopMoving() {
    this->b2_body->SetLinearVelocity(b2Vec2(0, 0));
}

void Body::destroy() {
    if (this->isDestroyed())
        return;
    this->world.b2_world->DestroyBody(this->b2_body);
    this->b2_body = nullptr;
    this->to_be_destroyed = false;
}

bool Body::isDestroyed() const {
    return this->b2_body == nullptr;
}

void Body::setToBeDestroyed() {
    this->to_be_destroyed = true;
}

bool Body::toBeDestroyed() const {
    return this->to_be_destroyed;
}

float Body::getX() const {
    return this->x;
}

float Body::getY() const {
    return this->y;
}

float Body::getAngle() const {
    return this->angle;
}

void Body::update() {
    if (this->isDestroyed())
        return;

    this->x = this->b2_body->GetPosition().x;
    this->y = this->b2_body->GetPosition().y;
    this->angle = this->b2_body->GetAngle();
}
