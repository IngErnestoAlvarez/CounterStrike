#include <arpa/inet.h>
#include <iostream>

#include "command_queue.h"
#include "peer.h"
#include "protocolo.h"
#include "game_logic/game.h"

Peer::Peer(int id, int game_id, socket_t &skt, Protocolo &protocol,
           CommandQueue& command_queue)
    : id(id),
      game_id(game_id),
      is_running(false),
      socket(std::move(skt)),
      protocol(protocol),
      command_queue(command_queue),
      state_queue(),
      sender(socket, protocol, state_queue),
      receiver(id, socket, protocol, command_queue) {
    // this->protocol.send_config(&this->socket);
}

Peer::~Peer() {
    this->sender.stop();
    this->receiver.stop();
    this->socket.shutdown();
    this->socket.close();
}

void Peer::start() {
    this->is_running = true;
    this->sender.start();
    this->receiver.start();
}

bool Peer::isRunning() {
    return this->is_running;
}

void Peer::pushGameState(Game& game) {
    GameState state = game.getState(this->id);
    this->state_queue.push(state);
}

int Peer::getGameID() {
    return this->game_id;
}
