#include "acceptor.h"
#include "peer.h"
#include <iostream>
#include "types.h"
#include <cassert>
#include <unistd.h>
#include <ctime>

#define LOOP_TIME 16 // milisegundos

inline int timeLeft(int next_time);

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
		this->accept();
		// this->accept();

		this->game.start();

		while (this->is_running && this->game.isRunning()) {
			std::time_t result = std::time(nullptr);
			int next_time = result * 1000 + LOOP_TIME;

			this->game.step();

			for (Peer* peer : this->peers)
				peer->sendState();

			// Command command(STOP, 0);
			// this->command_queue_monitor.pop(command);
			// this->game.executeCommand(command);
			for (int i = 0; i < 10; i++) {
				Command command = this->cmd_queue.pop();
				if (command.getCode() == NO_COMMAND) {
					std::cout << "empty queue" << std::endl;
					break;
				}

				std::cout << "Command { code = " << command.getCode() << ", peer_id = " << command.getPeerID() << "}" << std::endl;
				this->game.executeCommand(command);
			}

			usleep(timeLeft(next_time) * 1000);
		}
	} catch (...) {

	}
}

inline int timeLeft(int next_time) {
	std::time_t result = std::time(nullptr);
	int time = result * 1000;
	if (time > next_time)
		return 0;
	return next_time - time;
}

void Acceptor::stop() {
	this->is_running = false;
}

void Acceptor::accept() {
	socket_t peer_socket;
	this->socket.accept(&peer_socket);
	Peer* peer = new Peer(this->peers.size(),
						  peer_socket,
				   		  this->protocol,
		   				  this->command_queue_monitor,
		   				  this->cmd_queue);
	this->peers.push_back(peer);
	this->game.addPlayer(TEAM_A, peer->getPeerID());
	peer->start();
}
