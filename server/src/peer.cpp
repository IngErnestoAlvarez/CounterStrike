#include "peer.h"
#include <arpa/inet.h>
#include <iostream>

#include "Logger.h"
#include "protocolo.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Peer::Peer(int id, socket_t &socket, Protocolo &protocol,
           QueueMonitor<Command> &command_queue)
    : id(id),
      socket(std::move(socket)),
      protocol(protocol),
      command_queue(command_queue),
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
            // this->protocol.send_state(&this->socket);
            // this->protocol.send_player(&this->socket, this->id);
            Comando code = this->protocol.recv_comando(&this->socket);
            Command command(code, this->id);
            if (code == AIM) {
                std::cout << "aim" << std::endl;
                // uint16_t x = this->protocol.receive_two_bytes(&this->socket);
                // uint16_t y = this->protocol.receive_two_bytes(&this->socket);
                // x = ::ntohs(x);
                // y = ::ntohs(y);
                uint16_t angle = this->protocol.receive_two_bytes(&this->socket);
                angle = ::ntohs(angle);
                std::cout << "received angle: " << angle << std::endl;
                // std::cout << x << ", " << y << std::endl;
                command.setArg("angle", angle);
                // command.setArg("y", y);
            } else {
                std::cout << "recibi otro evento que no es aim" << std::endl;
            }
            this->command_queue.push(command);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR_PEER;
    }
}

void Peer::sendState() {
    this->protocol.send_state(&this->socket);
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
