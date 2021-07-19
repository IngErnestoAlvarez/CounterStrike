#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "peer.h"
#include "protocolo.h"
#include "game_logic/game.h"

Peer::Peer(int id, socket_t &skt, Protocolo &protocol,
           CommandQueue& command_queue)
    : id(id),
      socket(std::move(skt)),
      protocol(protocol),
      command_queue(command_queue),
      state_queue(),
      sender(socket, protocol, state_queue),
      receiver(id, socket, protocol, command_queue) {
    this->protocol.send_config(&this->socket);
}

Peer::~Peer() {
    this->sender.stop();
    this->receiver.stop();
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
