#include "protocolo.h"

#include <arpa/inet.h>

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "Logger.h"

Protocolo::Protocolo() {}

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

void Protocolo::recv_config(char **result, size_t *size, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    // descomentar esto (lo comento para evitar error de compilacion por
    // variables no usadas)

    uint16_t stencil_angle = this->receive_two_bytes(skt);
    uint16_t stencil_radius = this->receive_two_bytes(skt);
    uint16_t cell_count = this->receive_two_bytes(skt);
    cell_count = ::ntohs(cell_count);
    *size = cell_count;
    log->debug(std::to_string(cell_count).c_str());
    (*result) = new char[cell_count * 5];
    for (uint16_t i = 0; i < cell_count; i++) {
        int pos = i * 5;
        uint8_t type = this->receive_one_byte(skt);
        memcpy(&((*result)[pos]), &type, 1);
        uint16_t x = this->receive_two_bytes(skt);
        memcpy(&((*result)[pos + 1]), &x, 2);
        uint16_t y = this->receive_two_bytes(skt);
        memcpy(&((*result)[pos + 3]), &y, 2);
    }
    log->debug("Finalizado el recv_config");
}

void Protocolo::recv_state(char **result, size_t *size, uint8_t *roundResult,
                           socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    size_t rllyReceived;
    uint16_t aux;

    *roundResult = receive_one_byte(skt);

    aux = receive_two_bytes(skt);
    aux = ::ntohs(aux);
    (*size) = aux;
    (*result) = new char[(*size) * 9];
    log->debug("Se recibio como size en el recv_state: ");
    log->debug(std::to_string(*size).c_str());

    skt->receive(*result, (*size) * 9, rllyReceived);

    if (rllyReceived != ((*size) * 9)) {
        throw std::runtime_error(
            "Problemas al recibir el stream entero en recv_state");
    }
}

void Protocolo::send_comando(Comando comando, socket_t *skt) {
    skt->send((char *)&comando, COMMAND_SIZE);
}

void Protocolo::send_mouse(int x, int y, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se enviara lo siguiente a traves del send mouse: ");
    char message[4];
    assert(x < 65536);
    assert(y < 65536);
    uint16_t xaux = x;
    uint16_t yaux = y;
    xaux = htons(xaux);
    yaux = htons(yaux);
    this->send_comando(AIM, skt);
    send_two_bytes(skt, &xaux);
    send_two_bytes(skt, &yaux);

    log->debug(message);
}

void Protocolo::recv_player(char **result, size_t *size, socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    size_t rllyReceived;
    *size = 15;

    *result = new char[*size];

    skt->receive(*result, *size, rllyReceived);

    if (rllyReceived != *size) {
        free(*result);
        throw std::runtime_error(
            "Problemas al recibir el stream entero en recv_player");
    }

    log->debug("Se recibio como mensaje en el recv_player: ");
    log->debug(*result);
}

void Protocolo::send_angle(float angle, socket_t *skt) {
    std::cout << "Protocolo::send_angle(" << angle << ")" << std::endl;
    this->send_comando(AIM, skt);
    uint16_t aux = angle;
    aux = aux % 360;
    if (aux < 0) aux += 360;
    aux = htons(aux);
    this->send_two_bytes(skt, &aux);
}
