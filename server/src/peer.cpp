#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "Logger.h"
#include "peer.h"
#include "protocolo.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Peer::Peer(int id, socket_t &socket, Protocolo &protocol,
           CommandQueue& command_queue)
    : id(id),
      is_running(true),
      socket(std::move(socket)),
      protocol(protocol),
      command_queue(command_queue) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se envia config");
    this->protocol.send_config(&this->socket);
}

int Peer::getPeerID() const { return this->id; }

void Peer::run() {
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

    this->stop();
}

void Peer::sendState() {
    this->protocol.send_state(&this->socket, this->id);
    this->protocol.send_player(&this->socket, this->id);
}

void Peer::stop() {
    if (!this->is_running) return;

    this->is_running = false;
    this->socket.shutdown();
    this->socket.close();
}

bool Peer::isRunning() {
    return this->is_running;
}

Peer::~Peer() {
    this->stop();
    this->join();
}
