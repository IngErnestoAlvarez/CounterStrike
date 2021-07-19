#include "login_handler.h"
#include "configuration.h"
#include "login.h"
#include "login_queue.h"
#include <iostream>

LoginHandler::LoginHandler(const std::string& config_filepath, LoginQueue& login_queue)
	: login_queue(login_queue) {
	Configuration config(config_filepath);
    this->socket.bind_and_listen(nullptr, config.getPort().c_str(), 20);
}

void LoginHandler::run() {
	try {
		while (true) {
			socket_t peer;
			this->socket.accept(&peer);
			uint8_t game_id = this->protocol.receive_one_byte(&peer);
			uint8_t team_id = this->protocol.receive_one_byte(&peer);
			Login login(game_id, TeamID(team_id), peer);
			this->login_queue.push(login);
		}
	} catch (...) {}
}

void LoginHandler::stop() {
	this->socket.shutdown();
	this->socket.close();
}
