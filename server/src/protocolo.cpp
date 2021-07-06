#include "protocolo.h"

#include <arpa/inet.h>

#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "Logger.h"
#include "game_logic/body.h"
#include "game_logic/cell.h"
#include "game_logic/game.h"
#include "game_logic/map.h"

Protocolo::Protocolo() : game(nullptr) {}

Protocolo::Protocolo(Game *game) : game(game) {}

Protocolo::~Protocolo() {}

void Protocolo::send_one_byte(socket_t *skt, uint8_t *byte) {
    skt->send((char *)byte, 1);
}

void Protocolo::send_two_bytes(socket_t *skt, uint16_t *bytes) {
    skt->send((char *)bytes, 2);
}

void Protocolo::send_four_bytes(socket_t *skt, uint32_t *bytes) {
    skt->send((char *)bytes, 4);
}

uint8_t Protocolo::receive_one_byte(socket_t *skt) {
    uint8_t byte;
    size_t received;
    skt->receive((char *)&byte, 1, received);
    return byte;
}

uint16_t Protocolo::receive_two_bytes(socket_t *skt) {
    uint16_t bytes;
    size_t received;
    skt->receive((char *)&bytes, 2, received);
    return bytes;
}

uint32_t Protocolo::receive_four_bytes(socket_t *skt) {
    uint32_t bytes;
    size_t received;
    skt->receive((char *)&bytes, 4, received);
    return bytes;
}

void Protocolo::send_config(socket_t *skt) {
    Map &map = this->game->getMap();

    uint16_t stencil_angle = 45;
    stencil_angle = ::htons(stencil_angle);
    uint16_t stencil_radius = 100;
    stencil_radius = ::htons(stencil_radius);
    uint16_t cell_count = uint16_t(map.getWidth() * map.getHeight());
    cell_count = ::htons(cell_count);

    this->send_two_bytes(skt, &stencil_angle);
    this->send_two_bytes(skt, &stencil_radius);
    this->send_two_bytes(skt, &cell_count);

    for (Cell &cell : map) {
        uint8_t type = cell.getBodyType();

        uint16_t x = uint16_t(cell.getWorldX());
        x = ::htons(x);
        uint16_t y = uint16_t(cell.getWorldY());
        y = ::htons(y);

        this->send_one_byte(skt, &type);
        this->send_two_bytes(skt, &x);
        this->send_two_bytes(skt, &y);
    }
}

void Protocolo::recv_config(socket_t *skt) {
    // descomentar esto (lo comento para evitar error de compilacion por
    // variables no usadas)

    // uint16_t stencil_angle = this->receive_two_bytes(skt);
    // uint16_t stencil_radius = this->receive_two_bytes(skt);
    uint16_t cell_count = this->receive_two_bytes(skt);

    for (uint16_t i = 0; i < cell_count; i++) {
        // uint8_t type = this->receive_one_byte(skt);
        // uint16_t x = this->receive_two_bytes(skt);
        // uint16_t y = this->receive_two_bytes(skt);
    }
}

void Protocolo::send_state(socket_t *skt) {
    std::vector<Body *> bodies = this->game->getBodies();
    uint16_t body_count = bodies.size();
    body_count = ::htons(body_count);
    this->send_two_bytes(skt, &body_count);
    for (Body *body : bodies) {
        uint8_t type = uint8_t(body->getType());
        uint16_t x = uint16_t(body->getX());
        x = ::htons(x);
        uint16_t y = uint16_t(body->getY());
        y = ::htons(y);
        uint32_t angle = uint32_t(body->getAngle());
        angle = ::htonl(angle);
        this->send_one_byte(skt, &type);
        this->send_two_bytes(skt, &x);
        this->send_two_bytes(skt, &y);
        this->send_four_bytes(skt, &angle);
    }
}

void Protocolo::recv_state(char **result, size_t *size, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    size_t rllyReceived;
    uint16_t aux;

    skt->receive((char *)&aux, 2, rllyReceived);
    if (rllyReceived != 2) {
        throw std::runtime_error(
            "Problemas al recibir el estado. Se recibio una cantidad inexacta "
            "de bytes");
    }
    aux = ::ntohs(aux);
    (*size) = aux;
    log->debug("Se recibio como size en el recv_state: ");
    log->debug(std::to_string(*size).c_str());

    skt->receive(*result, *size, rllyReceived);

    if (rllyReceived != *size) {
        throw std::runtime_error(
            "Problemas al recibir el stream entero en recv_state");
    }

    log->debug("Se recibio como mensaje en el recv_state: ");
    log->debug(*result);
}

void Protocolo::send_comando(Comando comando, socket_t *skt) {
    skt->send((char *)&comando, COMMAND_SIZE);
}

Comando Protocolo::recv_comando(socket_t *skt) {
    char mesg;
    size_t bytes_received;
    skt->receive(&mesg, COMMAND_SIZE, bytes_received);
    return static_cast<Comando>(mesg);
}

void Protocolo::send_mouse(int x, int y, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se enviara lo siguiente a traves del send mouse: ");
    char message[4];
    uint16_t xaux = x;
    uint16_t yaux = y;
    xaux = htons(xaux);
    yaux = htons(yaux);
    memcpy(message, &xaux, 2);
    memcpy(&message[2], &yaux, 2);

    log->debug(message);
    skt->send(message, 4);
}

void Protocolo::recv_player(char **result, size_t *size, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    size_t rllyReceived;
    *size = 15;

    skt->receive(*result, *size, rllyReceived);

    if (rllyReceived != *size) {
        throw std::runtime_error(
            "Problemas al recibir el stream entero en recv_player");
    }

    log->debug("Se recibio como mensaje en el recv_player: ");
    log->debug(*result);
}

void Protocolo::send_player(socket_t *skt, int peer_id) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza send player");
    Player& player = *this->game->getPlayer(peer_id);
    uint8_t ammo = player.getAmmo();
    uint8_t life = player.getHealth();
    uint16_t money = ::htons(16000);
    uint16_t x = ::htons(uint16_t(player.getX()));
    uint16_t y = ::htons(uint16_t(player.getY()));
    float angleAux = player.getAngle();
    uint32_t angle = ::htonl(*(uint32_t *)&angleAux);
    uint8_t actualWeapon = AK47_TYPE;
    uint8_t time = 60;
    uint8_t gotBomb = uint8_t(false);
    log->debug("Comienza el envio de datos en send_player");

    send_one_byte(skt, &ammo);
    send_one_byte(skt, &life);
    send_two_bytes(skt, &money);
    send_two_bytes(skt, &x);
    send_two_bytes(skt, &y);
    send_four_bytes(skt, &angle);
    send_one_byte(skt, &actualWeapon);
    send_one_byte(skt, &time);
    send_one_byte(skt, &gotBomb);
}
