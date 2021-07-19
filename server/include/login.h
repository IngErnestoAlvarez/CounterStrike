#ifndef LOGIN_H
#define LOGIN_H

#include "socket.h"
#include "types.h"

class Login {
public:
	bool empty;
	int game_id;
	TeamID team_id;
	socket_t peer_socket;

	Login();
	Login(int game_id, TeamID team_id, socket_t& peer_socket);
	Login(Login&& other);
};

#endif
