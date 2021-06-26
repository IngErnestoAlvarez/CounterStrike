#include <cmath>
#include <Box2D/Box2D.h>
#include "game_logic/body.h"
#include "game_logic/world.h"

Body::Body(World& world, float x, float y, float velocity)
    : world(world), id(world.bodies.size()), velocity(velocity) {
    b2BodyDef b2_body_def;
    b2_body_def.position.Set(x, y);
    b2_body_def.angle = 0;
    b2_body_def.type = velocity > 0 ? b2_dynamicBody : b2_staticBody;
    b2_body_def.allowSleep = false;
    b2_body_def.userData = this;
    this->b2_body = this->world.b2_world->CreateBody(&b2_body_def);

    b2PolygonShape b2_polygon_shape;
    b2_polygon_shape.SetAsBox(10, 10);
    this->b2_body->CreateFixture(&b2_polygon_shape, 1);
}

Body::~Body() {
    if (this->b2_body != nullptr) {
        this->world.bodies[this->id] = nullptr;
        this->destroy();
    }
}

void Body::setAngle(float angle) {
    this->b2_body->SetTransform(this->b2_body->GetPosition(), angle);
}

void Body::move(float x_velocity, float y_velocity) {
    this->b2_body->SetLinearVelocity(b2Vec2(x_velocity, y_velocity));
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
    this->world.b2_world->DestroyBody(this->b2_body);
    this->b2_body = nullptr;
}

void Body::handleCollision(Body* other) {}

float Body::getX() const {
    return this->b2_body->GetPosition().x;
}

float Body::getY() const {
    return this->b2_body->GetPosition().y;
}

float Body::getAngle() const {
    return this->b2_body->GetAngle();
}
