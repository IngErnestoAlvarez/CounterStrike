#include "game_proxy/body_proxy.h"

#include <arpa/inet.h>

BodyProxy::BodyProxy() : bodies() {}

BodyProxy::~BodyProxy() {}

std::vector<BodyContainer>::iterator BodyProxy::getIterator() {
    return bodies.begin();
}

std::vector<BodyContainer>::iterator BodyProxy::getEnd() {
    return bodies.end();
}

void BodyProxy::setBodies(char *data, size_t n) {
    if (bodies.size() < n)
        setWithBiggerData(data, n);
    else
        setWithSmallerData(data, n);

    return;
}

void BodyProxy::setStatics(char *data, size_t n) {
    setStaticWithBiggerData(data, n);
}

void BodyProxy::setWithBiggerData(char *data, size_t n) {
    for (size_t i = 0; i < bodies.size(); i++) {
        size_t pos = i * size_t(sizeof(BodyContainer));
        bodies[i].tipo = BodyType(uint8_t(data[pos]));
        bodies[i].posx = ::ntohs(*(uint16_t *)&data[pos + 1]);
        bodies[i].posy = ::ntohs(*(uint16_t *)&data[pos + 3]);
        bodies[i].angle = float(::ntohl(*(uint32_t *)&data[pos + 5]));
    }

    for (size_t i = bodies.size(); i < n; i++) {
        BodyContainer aux;
        size_t pos = i * size_t(sizeof(BodyContainer));
        aux.tipo = BodyType(uint8_t(data[pos]));
        aux.posx = ::ntohs(*(uint16_t *)&data[pos + 1]);
        aux.posy = ::ntohs(*(uint16_t *)&data[pos + 3]);
        aux.angle = float(::ntohl(*(uint32_t *)&data[pos + 5]));
        bodies.push_back(aux);
    }
}

void BodyProxy::setWithSmallerData(char *data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        size_t pos = i * size_t(sizeof(BodyContainer));
        bodies[i].tipo = BodyType(uint8_t(data[pos]));
        bodies[i].posx = ::ntohs(*(uint16_t *)&data[pos + 1]);
        bodies[i].posy = ::ntohs(*(uint16_t *)&data[pos + 3]);
        bodies[i].angle = float(::ntohl(*(uint32_t *)&data[pos + 5]));
    }

    for (size_t i = 0; i < (bodies.size() - n); i++) {
        bodies.pop_back();
    }
}

void BodyProxy::setStaticWithBiggerData(char *data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        BodyContainer aux;
        size_t pos = (i * 5);
        aux.tipo = BodyType(*(uint8_t *)&data[pos]);
        aux.posx = (*(uint16_t *)&data[pos + 1]);
        aux.posy = (*(uint16_t *)&data[pos + 3]);
        aux.angle = 0;
        bodies.push_back(aux);
    }
}
