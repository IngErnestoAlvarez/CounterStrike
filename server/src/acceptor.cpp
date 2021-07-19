#include <cassert>
#include <ctime>
#include <iostream>
#include <unistd.h>

#include "acceptor.h"
#include "peer.h"
#include "types.h"
#include "login_queue.h"

#define LOOP_TIME 30

inline int getTimeLeft(int next_time);
inline int getTime();
inline void sleep(int time);

Acceptor::Acceptor(const std::string &config_filepath, LoginQueue& login_queue)
    : is_running(true),
      config(config_filepath),
      game(config, config.getMapFilepath()),
      protocol(&game),
      login_queue(login_queue) {
    // this->socket.bind_and_listen(nullptr, config.getPort().c_str(), 20);
}

Acceptor::~Acceptor() {
    if (this->is_running)
        this->stop();
}

void Acceptor::run() {
    try {
        // this->acceptPeers();
        // this->gameStart();

        while (this->is_running) {
            int next_time = getTime() + LOOP_TIME;

            this->acceptNewPeers();
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

void Acceptor::stop() {
    for (Peer *peer : this->peers)
        delete peer;

    this->is_running = false;
    this->join();
}

void Acceptor::acceptPeers() {
    // while (this->game.isInTeamsFormingPhase()) {
    //     socket_t peer_socket;
    //     this->socket.accept(&peer_socket);

    //     TeamID team_id = this->protocol.recv_login(&peer_socket);
    //     int peer_id = this->peers.size();

    //     if (!this->game.addPlayer(team_id, peer_id))
    //         continue;

    //     Peer *peer = new Peer(peer_id,
    //                           peer_socket,
    //                           this->protocol,
    //                           this->command_queue);

    //     this->peers.push_back(peer);
    // }
}

void Acceptor::sendStateToPeers() {
    for (Peer* peer : this->peers)
    	peer->pushGameState(*this->games[peer->getGameID()]);
}

void Acceptor::gameStart() {
    this->game.start();

    for (Peer *peer : this->peers) peer->start();
}

void Acceptor::gameStep() {
    for (auto& game : this->games) {
        if (!game.second->isInTeamsFormingPhase())
            game.second->start();
        game.second->step();
    }

    for (Peer* peer : this->peers) {
        if (!peer->isRunning())
            peer->start();
    }
}

void Acceptor::executePeerCommands() {
    while (true) {
        Command command = this->command_queue.pop();
        if (command.getCode() == NO_COMMAND) break;
        Peer* peer = this->peers[command.getPeerID()];
        this->games[peer->getGameID()]->executeCommand(command);
    }
}

void Acceptor::acceptNewPeers() {
    while (true) {
        Login login(std::move(this->login_queue.pop()));
        if (login.empty) break;

        int peer_id = this->peers.size();
        if (this->games.find(login.game_id) == this->games.end()) {
            this->games[login.game_id] = new Game(this->config, this->config.getMapFilepath());
            this->protocols[login.game_id] = new Protocolo(this->games[login.game_id]);
        }

        if (!this->games[login.game_id]->addPlayer(login.team_id, peer_id))
                continue;

        this->peers.push_back(new Peer(peer_id, login.game_id, login.peer_socket, *this->protocols[login.game_id], this->command_queue));
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
