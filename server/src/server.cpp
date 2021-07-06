#include "server.h"

#include <iostream>


Server::Server(const std::string& config_filepath)
	: acceptor(config_filepath) {}

Server::~Server() {}

void Server::run() {
	this->acceptor.start();
	while (getc(stdin) != 'q') {}
	this->acceptor.stop();
}
