#include "protocolo.h"

#include <stdexcept>

Protocolo::Protocolo(socket_t *skt) : skt(skt) {}

Protocolo::~Protocolo() {}

void Protocolo::send_comando(Comando comando) {
    skt->send((char *)&comando, COMMAND_SIZE);
}

void Protocolo::recv_comando(Comando *comando) {
    char mesg;
    size_t bytes_received;
    skt->receive(&mesg, COMMAND_SIZE, bytes_received);
    (*comando) = static_cast<Comando>(mesg);
