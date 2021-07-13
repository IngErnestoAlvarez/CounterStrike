#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <string>
#include <vector>

#include "command.h"
#include "command_queue.h"
#include "my_thread.h"
#include "game_logic/game.h"
#include "protocolo.h"
#include "socket.h"

class Peer;

class Acceptor : public Thread {
private:
	bool is_running;
	Game game;
	socket_t socket;
	Protocolo protocol;
	std::vector<Peer*> peers;
	CommandQueue command_queue;
	void acceptPeers();
	void sendStateToPeers();
	void gameStart();
	void gameStep();
	void executePeerCommands();

public:
	Acceptor(const std::string& config_filepath);
	void run() override;
	void stop();
	~Acceptor() override;
};

#endif
