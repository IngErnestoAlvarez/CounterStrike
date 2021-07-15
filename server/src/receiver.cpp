#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "Logger.h"
#include "peer.h"
#include "protocolo.h"
#include "socket.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Receiver::Receiver(
      int id,
      socket_t &socket,
      Protocolo &protocol,
      CommandQueue& command_queue)
    : id(id),
      is_running(true),
      socket(socket),
      protocol(protocol),
      command_queue(command_queue) {}

Receiver::~Receiver() {
    this->join();
}

void Receiver::run() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();

    try {
        while (true) {
            Comando code = this->protocol.recv_comando(&this->socket);
            Command command(code, this->id);

            if (code == AIM) {
                uint16_t angle = this->protocol.receive_two_bytes(&this->socket);
                angle = ::ntohs(angle);
                command.setArg("angle", angle);
            }

            this->command_queue.push(command);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR_PEER;
    }

    log->debug("termina Receiver::run");
}
