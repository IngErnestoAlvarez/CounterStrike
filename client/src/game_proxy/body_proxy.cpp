#include "game_proxy/body_proxy.h"

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

void BodyProxy::setWithBiggerData(char *data, size_t n) {
    for (size_t i = 0; i < bodies.size(); i++) {
        size_t pos = i * size_t(sizeof(BodyContainer));
        bodies[i].tipo = uint8_t(data[i]);
        bodies[i].posx = uint16_t(data[i + 1]);
        bodies[i].posy = uint16_t(data[i + 3]);
        bodies[i].angle = float(data[i + 5]);
    }

    for (size_t i = bodies.size(); i < n; i++) {
        BodyContainer aux;
        aux.tipo = uint8_t(data[i]);
        aux.posx = uint16_t(data[i + 1]);
        aux.posy = uint16_t(data[i + 3]);
        aux.angle = float(data[i + 5]);
        bodies.push_back(aux);
    }
}

void BodyProxy::setWithSmallerData(char *data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        size_t pos = i * size_t(sizeof(BodyContainer));
        bodies[i].tipo = uint8_t(data[i]);
        bodies[i].posx = uint16_t(data[i + 1]);
        bodies[i].posy = uint16_t(data[i + 3]);
        bodies[i].angle = float(data[i + 5]);
    }

    for (size_t i = 0; i < (bodies.size() - n); i++) {
        bodies.pop_back();
    }
}
