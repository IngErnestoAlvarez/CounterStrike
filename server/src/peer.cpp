#include <iostream>

#include "peer.h"
#include "protocolo.h"

#define UNEXPECTED_ERROR_PEER "Se ha producido un error inesperado en peer"

Peer::Peer(int id,
		   socket_t& socket,
		   Protocolo& protocol,
		   QueueMonitor<Command>& command_queue)
	: id(id),
	  socket(std::move(socket)),
	  protocol(protocol),
	  command_queue(command_queue),
	  is_running(true) {
	this->protocol.send_config(&this->socket);
}

int Peer::getPeerID() const {
	return this->id;
}

void Peer::run() {
	try {
		while (this->is_running) {
			// this->protocol.send_state(&this->socket);
			this->protocol.send_player(&this->socket, this->id);
			Comando code = this->protocol.recv_comando(&this->socket);
			Command command(code, this->id);
			if (code == AIM) {
				uint16_t x = this->protocol.receive_two_bytes(&this->socket);
				uint16_t y = this->protocol.receive_two_bytes(&this->socket);
				command.setArg("x", x);
				command.setArg("y", y);
			}
			this->command_queue.push(command);
		}
	} catch (const std::exception& e) {
		std::cerr << e.what();
	} catch (...) {
		std::cerr << UNEXPECTED_ERROR_PEER;
	}
}
	
void Peer::stop() {
	if (!this->is_running)
		return;

	this->is_running = false;
	this->socket.shutdown();
	this->socket.close();
}

Peer::~Peer() {
	this->stop();
	this->join();
}
