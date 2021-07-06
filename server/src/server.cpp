#include "server.h"

#include <iostream>

#include "Logger.h"

Server::Server()
    : game("config/config.yaml", "assets/maps/map.yaml"),
      protocolo(&game),
      socket() {
    this->socket.bind_and_listen("localhost", "8000", 20);
}

Server::~Server() {}

void Server::run() {
    socket_t peer;
    this->socket.accept(&peer);
    this->protocolo.send_config(&peer);
}
