#ifndef SERVER_H
#define SERVER_H

#include "game_logic/game.h"
#include "protocolo.h"
#include "socket.h"

class Server {
private:
	Game game;
	Protocolo protocolo;
	socket_t socket;

public:
	Server();
	~Server();

	void run();
};

#endif
