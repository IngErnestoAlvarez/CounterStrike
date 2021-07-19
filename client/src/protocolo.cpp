#include "protocolo.h"

#include <arpa/inet.h>

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "Logger.h"

#define BodyWithNOAngleSize 5
#define BodyWithAngleSize 9

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

    uint16_t stencil_angle __attribute__((unused)) =
        this->receive_two_bytes(skt);
    uint16_t stencil_radius __attribute__((unused)) =
        this->receive_two_bytes(skt);
    uint16_t cell_count = this->receive_two_bytes(skt);
    cell_count = ::ntohs(cell_count);
    *size = cell_count;
    log->debug(std::to_string(cell_count).c_str());
    (*result) = new char[cell_count * BodyWithNOAngleSize];
    for (uint16_t i = 0; i < cell_count; i++) {
        int pos = i * BodyWithNOAngleSize;
        uint8_t type = this->receive_one_byte(skt);
        memcpy(&((*result)[pos]), &type, 1);
        uint16_t x = this->receive_two_bytes(skt);
        memcpy(&((*result)[pos + 1]), &x, 2);
        uint16_t y = this->receive_two_bytes(skt);
        memcpy(&((*result)[pos + 3]), &y, 2);
    }
    log->debug("Finalizado el recv_config");
}

void Protocolo::recv_state(char **bodiesInStream, size_t *size,
                           uint8_t *roundResult, Phase *gamePhase,
                           uint8_t *teamAWins, uint8_t *teamBWins,
                           socket_t *skt) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    size_t rllyReceived;
    uint16_t aux;
    uint8_t phaseAux;

    // 1 byte for game phase
    phaseAux = receive_one_byte(skt);
    *gamePhase = Phase(phaseAux);

    // 1 byte for round state
    *roundResult = receive_one_byte(skt);

    // 1 byte para cada equipo (Son sus rondas ganadas)
    *teamAWins = receive_one_byte(skt);
    *teamBWins = receive_one_byte(skt);

    // 2 bytes for bodies.size()
    aux = receive_two_bytes(skt);
    aux = ::ntohs(aux);

    (*size) = aux;
    (*bodiesInStream) = new char[(*size) * BodyWithAngleSize];
    log->debug("Se recibio como size en el recv_state: ");
    log->debug(std::to_string(*size).c_str());

    skt->receive(*bodiesInStream, (*size) * BodyWithAngleSize, rllyReceived);

    if (rllyReceived != ((*size) * BodyWithAngleSize)) {
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
    assert(x < 65536);
    assert(y < 65536);
    uint16_t xaux = x;
    uint16_t yaux = y;
    xaux = htons(xaux);
    yaux = htons(yaux);
    this->send_comando(AIM, skt);
    send_two_bytes(skt, &xaux);
    send_two_bytes(skt, &yaux);
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

void Protocolo::send_login(socket_t *skt, TeamID team_id) {
    send_one_byte(skt, (uint8_t *)&team_id);
}

void Protocolo::recv_final(FinalScores &fScores, socket_t *skt) {
    // teamID 1
    TeamID team = TeamID(receive_one_byte(skt));
    fScores.setWinnerTeam(team);

    // teamAsize 2
    size_t teamAsize = size_t(::ntohs(receive_two_bytes(skt)));
    std::cout << "Se recibe el team size: " << teamAsize << std::endl;
    for (size_t i = 0; i < teamAsize; i++) {
        // namesize 1
        uint8_t nameSize = receive_one_byte(skt);

        char *name = new char[nameSize];
        size_t received;
        skt->receive(name, nameSize, received);

        if (received != nameSize) {
            delete name;
            throw std::runtime_error(
                "No se recibieron la cant de bytes necesarios. recv_final()");
        }
        uint16_t kills = ::ntohs(receive_two_bytes(skt));
        uint16_t deaths = ::ntohs(receive_two_bytes(skt));
        uint16_t totMoney = ::ntohs(receive_two_bytes(skt));

        fScores.addPlayerA(name, kills, deaths, totMoney);

        delete name;
    }

    size_t teamBsize = size_t(::ntohs(receive_two_bytes(skt)));
    for (size_t i = 0; i < teamBsize; i++) {
        uint8_t nameSize = receive_one_byte(skt);

        char *name = new char[nameSize];
        size_t received;
        skt->receive(name, nameSize, received);

        if (received != nameSize) {
            delete name;
            throw std::runtime_error(
                "No se recibieron la cant de bytes necesarios. recv_final()");
        }
        uint16_t kills = ::ntohs(receive_two_bytes(skt));
        uint16_t deaths = ::ntohs(receive_two_bytes(skt));
        uint16_t totMoney = ::ntohs(receive_two_bytes(skt));

        fScores.addPlayerB(name, kills, deaths, totMoney);

        delete name;
    }
}

void Protocolo::send_angle(float angle, socket_t *skt) {
    std::cout << "Protocolo::send_angle(" << angle << ")" << std::endl;
    this->send_comando(AIM, skt);
    uint16_t aux = angle - 90;
    aux = aux % 360;
    if (aux < 0) aux += 360;
    aux = htons(aux);
    this->send_two_bytes(skt, &aux);
}
