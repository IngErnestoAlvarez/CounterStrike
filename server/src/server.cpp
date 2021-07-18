#include "server.h"

#include <iostream>

#include "Logger.h"

Server::Server(const std::string &config_filepath)
    : acceptor(config_filepath) {}

Server::~Server() {}

void Server::run() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Entra al run");
    this->acceptor.start();
    while (getc(stdin) != 'q') {
    }
    this->acceptor.stop();
}
