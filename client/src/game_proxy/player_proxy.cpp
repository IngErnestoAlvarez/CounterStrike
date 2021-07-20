#include "game_proxy/player_proxy.h"

#include <arpa/inet.h>

#include <iostream>
#include <mutex>

typedef std::lock_guard<std::mutex> guard;

PlayerProxy::PlayerProxy(BodyType type) : type(type) {}

PlayerProxy::~PlayerProxy() {}

int PlayerProxy::getX() {
    guard guard(mutex);
    return posx;
}

int PlayerProxy::getY() {
    guard guard(mutex);
    return posy;
}

float PlayerProxy::getAngle() {
    guard guard(mutex);
    return angle;
}

int PlayerProxy::getLife() {
    guard guard(mutex);
    return life;
}

BodyType PlayerProxy::getType() {
    guard guard(mutex);
    return type;
}

WeaponProxy *PlayerProxy::getWeapon() { return &equipped_weapon; }

void PlayerProxy::setPlayer(char *data, size_t n) {
    guard guard(mutex);
    equipped_weapon.setAmmo(int(*(uint8_t *)&data[0]));
    life = int(*(uint8_t *)&data[1]);
    money = int(::ntohs(*(uint16_t *)&data[2]));
    posx = int(::ntohs(*(uint16_t *)&data[4]));
    posy = int(::ntohs(*(uint16_t *)&data[6]));
    uint32_t angleAux = ::ntohl(*(uint32_t *)&data[8]);

    angle = *(float *)&angleAux;
    angle = angle * 180 / 3.141592 + 90;

    equipped_weapon.setWeapon(int(*(uint8_t *)&data[12]));
    time = int(*(uint8_t *)&data[13]);
    gotBomb = bool(*(uint8_t *)&data[14]);
}
