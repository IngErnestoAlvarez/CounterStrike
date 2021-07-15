#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "Logger.h"
#include "peer.h"
#include "protocolo.h"
#include "game_logic/game.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Peer::Peer(int id, socket_t &skt, Protocolo &protocol,
           CommandQueue& command_queue)
    : id(id),
      is_running(true),
      socket(std::move(skt)),
      protocol(protocol),
      command_queue(command_queue),
      state_queue(),
      sender(socket, protocol, state_queue),
      receiver(id, socket, protocol, command_queue) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Se enviara config a peer");
    this->protocol.send_config(&this->socket);
    log->debug("se envio config a peer");
}

Peer::~Peer() {
    this->socket.shutdown();
    this->socket.close();
}

void Peer::start() {
    this->sender.start();
    this->receiver.start();
}

void Peer::pushGameState(Game& game) {
    GameState state = game.getState(this->id);
    this->state_queue.push(state);
}
