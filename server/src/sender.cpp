#include <arpa/inet.h>
#include <iostream>

#include "state_queue.h"
#include "peer.h"
#include "protocolo.h"
#include "socket.h"
#include "sender.h"
#include "game_state.h"

Sender::Sender(
      socket_t &socket,
      Protocolo &protocol,
      StateQueue& state_queue)
    : is_running(true),
      socket(socket),
      protocol(protocol),
      state_queue(state_queue) {}

Sender::~Sender() {
    this->join();
}

void Sender::run() {
    try {
        this->protocol.send_config(&this->socket);

        GameState state;

        while (this->state_queue.pop(state)) {
            this->protocol.send_one_byte(&this->socket, &state.ammo);
            this->protocol.send_one_byte(&this->socket, &state.health);
            this->protocol.send_two_bytes(&this->socket, &state.money);
            this->protocol.send_two_bytes(&this->socket, &state.x);
            this->protocol.send_two_bytes(&this->socket, &state.y);
            this->protocol.send_four_bytes(&this->socket, &state.angle);
            this->protocol.send_one_byte(&this->socket, &state.weapon);
            this->protocol.send_one_byte(&this->socket, &state.time);
            this->protocol.send_one_byte(&this->socket, &state.has_bomb);
            // this->protocol.send_one_byte(&this->socket, &state.body_type);

            this->protocol.send_one_byte(&this->socket, &state.phase);
            this->protocol.send_one_byte(&this->socket, &state.winner_team_id);
            this->protocol.send_one_byte(&this->socket, &state.team_a_wins);
            this->protocol.send_one_byte(&this->socket, &state.team_b_wins);
            this->protocol.send_two_bytes(&this->socket, &state.body_count);

            for (auto& body : state.bodies) {
                this->protocol.send_one_byte(&this->socket, &body.type);
                this->protocol.send_two_bytes(&this->socket, &body.x);
                this->protocol.send_two_bytes(&this->socket, &body.y);
                this->protocol.send_four_bytes(&this->socket, &body.angle);
            }

            if (Phase(state.phase) == FINAL_PHASE)
                this->state_queue.kill();
        }

        this->protocol.send_final(&this->socket);
    } catch (const socket_t::SocketClosed& e) {
        if (this->is_running)
            std::cerr << e.what();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << "Unexpected error in sender thread\n";
    }
}

void Sender::stop() {
    this->is_running = false;
    this->state_queue.kill();
}
