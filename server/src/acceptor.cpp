#include "acceptor.h"
#include "peer.h"
#include <iostream>
#include "types.h"
#include <cassert>

Acceptor::Acceptor(const std::string& config_filepath)
	: game(config_filepath, "assets/maps/map.yaml"),
	  protocol(&game),
	  command_queue(),
	  command_queue_monitor(&command_queue),
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
		this->game.start();

		while (this->is_running && this->game.isRunning()) {
			this->game.step();

			for (Peer* peer : this->peers)
				peer->sendState();

			Command command(STOP, 0);
			this->command_queue_monitor.pop(command);

			this->game.executeCommand(command);
		}
	} catch (...) {

	}
}

void Acceptor::stop() {
	this->is_running = false;
}

void Acceptor::accept() {
	socket_t peer_socket;
	std::cout << "Acceptor::accept()" << std::endl;
	this->socket.accept(&peer_socket);
	std::cout << "after socket.accept()" << std::endl;
	Peer* peer = new Peer(this->peers.size(),
						  peer_socket,
				   		  this->protocol,
		   				  this->command_queue_monitor);
	this->peers.push_back(peer);
	this->game.addPlayer(TEAM_A, peer->getPeerID());
	peer->start();
}
