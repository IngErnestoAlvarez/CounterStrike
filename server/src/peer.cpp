#include "peer.h"
#include <arpa/inet.h>
#include <iostream>

#include "Logger.h"
#include "protocolo.h"
#include "command_queue.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Peer::Peer(int id, socket_t &socket, Protocolo &protocol,
           QueueMonitor<Command> &command_queue, CommandQueue& cmd_queue)
    : id(id),
      socket(std::move(socket)),
      protocol(protocol),
      command_queue(command_queue),
      cmd_queue(cmd_queue),
      is_running(true) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se envia config");
    this->protocol.send_config(&this->socket);
}

int Peer::getPeerID() const { return this->id; }

void Peer::run() {
    try {
        while (this->is_running) {
            Comando code = this->protocol.recv_comando(&this->socket);
            Command command(code, this->id);
            if (code == AIM) {
                uint16_t angle = this->protocol.receive_two_bytes(&this->socket);
                angle = ::ntohs(angle);
                command.setArg("angle", angle);
            }
            this->cmd_queue.push(command);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR_PEER;
    }
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

Peer::~Peer() {
    this->stop();
    this->join();
}
