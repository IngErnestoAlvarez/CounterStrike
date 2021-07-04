#include "protocolo.h"
#include "game_logic/body.h"
#include "game_logic/game.h"
#include "game_logic/map.h"
#include <vector>
#include <stdexcept>

Protocolo::Protocolo() : game(nullptr) {}

Protocolo::Protocolo(Game* game) : game(game) {}

Protocolo::~Protocolo() {}

void Protocolo::send_one_byte(socket_t* skt, uint8_t* byte) {
    skt->send((char*)byte, 1);
}

void Protocolo::send_two_bytes(socket_t* skt, uint16_t* bytes) {
    skt->send((char*)bytes, 2);
}

uint8_t Protocolo::receive_one_byte(socket_t* skt) {
    uint8_t byte;
    size_t received;
    skt->receive((char*)&byte, 1, received);
    return byte;
}

uint16_t Protocolo::receive_two_bytes(socket_t* skt) {
    uint16_t bytes;
    size_t received;
    skt->receive((char*)&bytes, 2, received);
    return bytes;
}

void Protocolo::send_config(socket_t* skt) {
    Map& map = this->game->getMap();

    uint16_t stencil_angle = 45;
    uint16_t stencil_radius = 100;
    uint16_t cell_count = uint16_t(map.getWidth() * map.getHeight());

    this->send_two_bytes(skt, &stencil_angle);
    this->send_two_bytes(skt, &stencil_radius);
    this->send_two_bytes(skt, &cell_count);

    for (Cell& cell : map) {
        uint8_t type = cell.canBeAccesed()
             ? OFFICE_TYPE : cell.getBody()->getType();

        uint16_t x = uint16_t(cell.getWorldX());
        uint16_t y = uint16_t(cell.getWorldY());

        this->send_one_byte(skt, &type);
        this->send_two_bytes(skt, &x);
        this->send_two_bytes(skt, &y);
    }
}

void Protocolo::recv_config(socket_t* skt) {
    // descomentar esto (lo comento para evitar error de compilacion por variables no usadas)

    // uint16_t stencil_angle = this->receive_two_bytes(skt);
    // uint16_t stencil_radius = this->receive_two_bytes(skt);
    uint16_t cell_count = this->receive_two_bytes(skt);

    for (uint16_t i = 0; i < cell_count; i++) {
        // uint8_t type = this->receive_one_byte(skt);
        // uint16_t x = this->receive_two_bytes(skt);
        // uint16_t y = this->receive_two_bytes(skt);
    }
}

void Protocolo::send_comando(Comando comando, socket_t* skt) {
    skt->send((char *)&comando, COMMAND_SIZE);
}

void Protocolo::recv_comando(Comando *comando, socket_t* skt) {
    char mesg;
    size_t bytes_received;
    skt->receive(&mesg, COMMAND_SIZE, bytes_received);
    (*comando) = static_cast<Comando>(mesg);
}
