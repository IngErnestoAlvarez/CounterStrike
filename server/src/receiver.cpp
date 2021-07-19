#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "peer.h"
#include "protocolo.h"
#include "socket.h"

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

void Receiver::stop() {
    this->is_running = false;
}

void Receiver::run() {
    try {
        while (true) {
            Comando code = this->protocol.recv_comando(&this->socket);
            Command command(code, this->id);

            if (code == AIM) {
                uint16_t angle = this->protocol.receive_two_bytes(
                    &this->socket);
                angle = ::ntohs(angle);
                command.setArg("angle", angle);
            }

            this->command_queue.push(command);
        }
    } catch (const socket_t::SocketClosed& e) {
        if (this->is_running)
            std::cerr << e.what();
    } catch (const std::exception &e) {
        if (this->is_running)
            std::cerr << e.what();
    } catch (...) {
        std::cerr << "Unexpected error in receiver thread\n";
    }
}
