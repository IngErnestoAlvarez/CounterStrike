#include <iostream>

#include "server.h"

Server::Server(const std::string &config_filepath)
    : login_queue(),
      login_handler(config_filepath, login_queue),
      acceptor(config_filepath, login_queue) {}

Server::~Server() {}

void Server::run() {
    this->login_handler.start();
    this->acceptor.start();
    while (getc(stdin) != 'q') {}
    this->acceptor.stop();
    this->login_handler.stop();
}
