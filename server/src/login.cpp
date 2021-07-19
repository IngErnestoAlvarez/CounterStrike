#include "login.h"

Login::Login() : empty(true) {}

Login::Login(int game_id, TeamID team_id, socket_t& socket)
	: game_id(game_id), team_id(team_id), peer_socket(std::move(socket)) {

}

Login::Login(Login&& other) {
	this->empty = other.empty;
	this->game_id = other.game_id;
	this->team_id = other.team_id;
	this->peer_socket = std::move(other.peer_socket);
}
