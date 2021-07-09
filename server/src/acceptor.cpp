#include "acceptor.h"
#include "peer.h"
#include <iostream>
#include "types.h"
#include <cassert>
#include <unistd.h>
#include <ctime>
#include "Logger.h"

#define LOOP_TIME 30 // milisegundos

inline int getTimeLeft(int next_time);
inline int getTime();
inline void sleep(int time);

inline int timeLeft(int next_time);

inline int timeLeft(int next_time) {
	std::time_t result = std::time(nullptr);
	int time = result * 1000;
	if (time > next_time)
		return 0;
	return next_time - time;
}


Acceptor::Acceptor(const std::string& config_filepath)
	: game(config_filepath, "assets/maps/map.yaml"),
	  protocol(&game),
	  command_queue(),
	  command_queue_monitor(&command_queue),
	  cmd_queue(),
	  is_running(true) {
	this->socket.bind_and_listen(nullptr, "8000", 20);
}

Acceptor::~Acceptor() {
	this->socket.shutdown();
	this->socket.close();
	this->join();
	for (Peer* peer : this->peers)
		delete peer;
}

void Acceptor::run() {
	try {
		this->acceptPeers();
		this->gameStart();

		for (Peer* peer : this->peers)
			peer->start();

		while (this->is_running) {
			int next_time = getTime() + LOOP_TIME;

			// std::time_t result = std::time(nullptr);
			// int next_time = result * 1000 + LOOP_TIME;

			this->gameStep();
			this->sendStateToPeers();
			this->executePeerCommands();

			sleep(getTimeLeft(next_time));

			// usleep(timeLeft(next_time) * 1000);
		}
	} catch (...) {

	}
}

void Acceptor::stop() {
	this->is_running = false;
}

void Acceptor::acceptPeers() {
	using namespace CPlusPlusLogging;
	Logger *log = Logger::getInstance();

	TeamID team_id;
	int peer_id;

	while (this->game.isInTeamsFormingPhase()) {
    	log->debug("Esperando nuevo peer");
		socket_t peer_socket;
		this->socket.accept(&peer_socket);
		log->debug("Nuevo peer aceptado");
		team_id = this->protocol.recv_login(&peer_socket);
		std::string debug = "Se recibio login - team_id = " + std::to_string(team_id);
		log->debug(debug);
		peer_id = this->peers.size();

		if (!this->game.addPlayer(team_id, peer_id)) {
			continue;
		}

		Peer* peer = new Peer(this->peers.size(),
						peer_socket,
						this->protocol,
						this->command_queue_monitor,
						this->cmd_queue);
		log->debug("Se crea peer");
		this->peers.push_back(peer);
		// peer->start();
	}
}

void Acceptor::sendStateToPeers() {
	for (Peer* peer : this->peers)
		peer->sendState();
}

void Acceptor::gameStart() {
	this->game.start();
}

void Acceptor::gameStep() {
	this->game.step();
}

void Acceptor::executePeerCommands() {
	for (int i = 0; i < 10; i++) {
		Command command = this->cmd_queue.pop();
		if (command.getCode() == NO_COMMAND)
			break;
		this->game.executeCommand(command);
	}
}

inline int getTimeLeft(int next_time) {
	std::time_t result = std::time(nullptr);
	int time = result * 1000;
	if (time > next_time)
		return 0;
	return next_time - time;
}

inline int getTime() {
	return std::time(nullptr) * 1000;
}

inline void sleep(int time) {
	usleep(time * 1000);
}
