#include <cassert>
#include <ctime>
#include <iostream>
#include <unistd.h>

#include "acceptor.h"
#include "peer.h"
#include "types.h"

#define LOOP_TIME 30

inline int getTimeLeft(int next_time);
inline int getTime();
inline void sleep(int time);

Acceptor::Acceptor(const std::string &config_filepath)
    : is_running(true),
      config(config_filepath),
      game(config, config.getMapFilepath()),
      protocol(&game) {
    this->socket.bind_and_listen(nullptr, config.getPort().c_str(), 20);
}

Acceptor::~Acceptor() {
    for (Peer *peer : this->peers)
        delete peer;

    this->socket.shutdown();
    this->socket.close();
    this->is_running = false;
    this->join();
}

void Acceptor::run() {
    try {
        this->acceptPeers();
        this->gameStart();

        while (this->is_running) {
            int next_time = getTime() + LOOP_TIME;

            this->gameStep();
            this->sendStateToPeers();
            this->executePeerCommands();

            sleep(getTimeLeft(next_time));
        }
    } catch (const std::exception& e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << "Unexpected error in acceptor thread\n";
    }
}

void Acceptor::stop() { this->is_running = false; }

void Acceptor::acceptPeers() {
    while (this->game.isInTeamsFormingPhase()) {
        socket_t peer_socket;
        this->socket.accept(&peer_socket);

        TeamID team_id = this->protocol.recv_login(&peer_socket);
        int peer_id = this->peers.size();

        if (!this->game.addPlayer(team_id, peer_id))
            continue;

        Peer *peer = new Peer(peer_id,
                              peer_socket,
                              this->protocol,
                              this->command_queue);

        this->peers.push_back(peer);
    }
}

void Acceptor::sendStateToPeers() {
    for (Peer* peer : this->peers)
    	peer->pushGameState(this->game);
}

void Acceptor::gameStart() {
    this->game.start();

    for (Peer *peer : this->peers) peer->start();
}

void Acceptor::gameStep() { this->game.step(); }

void Acceptor::executePeerCommands() {
    while (true) {
        Command command = this->command_queue.pop();
        if (command.getCode() == NO_COMMAND) break;
        this->game.executeCommand(command);
    }
}

inline int getTimeLeft(int next_time) {
    std::time_t result = std::time(nullptr);
    int time = result * 1000;
    if (time > next_time) return 0;
    return next_time - time;
}

inline int getTime() { return std::time(nullptr) * 1000; }

inline void sleep(int time) { usleep(time * 1000); }
