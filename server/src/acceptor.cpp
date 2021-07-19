#include "acceptor.h"

#include <unistd.h>

#include <cassert>
#include <ctime>
#include <iostream>

#include "Logger.h"
#include "peer.h"
#include "types.h"

#define LOOP_TIME 30  // milisegundos

inline int getTimeLeft(int next_time);
inline int getTime();
inline void sleep(int time);

inline int timeLeft(int next_time);

inline int timeLeft(int next_time) {
    std::time_t result = std::time(nullptr);
    int time = result * 1000;
    if (time > next_time) return 0;
    return next_time - time;
}

Acceptor::Acceptor(const std::string &config_filepath)
    : is_running(true),
      config(config_filepath),
      game(config, "assets/maps/map_2.yaml"),
      protocol(&game) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza constructor acceptor");
    this->socket.bind_and_listen(nullptr, config.getPort().c_str(), 20);
}

Acceptor::~Acceptor() {
    for (Peer *peer : this->peers) delete peer;

    this->socket.shutdown();
    this->socket.close();

    this->join();
}

void Acceptor::run() {
    try {
        this->acceptPeers();
        this->gameStart();

        while (this->is_running) {
            int next_time = getTime() + LOOP_TIME;

            this->gameStep();

            for (Peer *peer : this->peers) {
                peer->pushGameState(this->game);
            }

            this->executePeerCommands();

            sleep(getTimeLeft(next_time));
        }
    } catch (...) {
    }
}

void Acceptor::stop() { this->is_running = false; }

void Acceptor::acceptPeers() {
    TeamID team_id;
    int peer_id;

    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();

    while (this->game.isInTeamsFormingPhase()) {
        log->debug("esperando nuevo peer");
        socket_t peer_socket;
        this->socket.accept(&peer_socket);
        log->debug("se acepto peer");
        team_id = this->protocol.recv_login(&peer_socket);
        log->debug("se recibio login");
        peer_id = this->peers.size();

        if (!this->game.addPlayer(team_id, peer_id)) {
            continue;
        }

        Peer *peer = new Peer(this->peers.size(), peer_socket, this->protocol,
                              this->command_queue);

        this->peers.push_back(peer);
    }
}

void Acceptor::sendStateToPeers() {
    // for (Peer* peer : this->peers) {
    // 	if (peer->isRunning())
    // 		peer->sendState();
    // }
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
