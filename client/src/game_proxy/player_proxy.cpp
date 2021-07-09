#include "game_proxy/player_proxy.h"

#include <arpa/inet.h>

#include <iostream>

PlayerProxy::PlayerProxy(BodyType type) : type(type) {}

PlayerProxy::~PlayerProxy() {}

int PlayerProxy::getX() { return posx; }

int PlayerProxy::getY() { return posy; }

float PlayerProxy::getAngle() { return angle; }

int PlayerProxy::getLife() { return life; }

BodyType PlayerProxy::getType() { return type; }

WeaponProxy *PlayerProxy::getWeapon() { return &equipped_weapon; }

void PlayerProxy::setPlayer(char *data, size_t n) {
    equipped_weapon.setAmmo(int(*(uint8_t *)&data[0]));
    life = int(*(uint8_t *)&data[1]);
    money = int(::ntohs(*(uint16_t *)&data[2]));
    posx = int(::ntohs(*(uint16_t *)&data[4]));
    posy = int(::ntohs(*(uint16_t *)&data[6]));
    uint32_t angleAux = ::ntohl(*(uint32_t *)&data[8]);
    std::cout << "angleAux: " << angleAux << std::endl;
    angle = *(float *)&angleAux;
    angle = angle * 180 / 3.141592 + 90;
    std::cout << "angle: " << angle << std::endl;
    equipped_weapon.setWeapon(int(*(uint8_t *)&data[12]));
    time = int(*(uint8_t *)&data[13]);
    gotBomb = bool(*(uint8_t *)&data[14]);
}
