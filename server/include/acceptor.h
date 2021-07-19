#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <string>
#include <vector>
#include <unordered_map>

#include "command.h"
#include "command_queue.h"
#include "configuration.h"
#include "my_thread.h"
#include "game_logic/game.h"
#include "protocolo.h"
#include "socket.h"

class Peer;
class LoginQueue;

class Acceptor : public Thread {
private:
	bool is_running;
	Configuration config;
	Game game;
	socket_t socket;
	Protocolo protocol;
	LoginQueue& login_queue;
	std::vector<Peer*> peers;
	std::unordered_map<int, Protocolo*> protocols;
	std::unordered_map<int, Game*> games;
	CommandQueue command_queue;
	void acceptPeers();
	void acceptNewPeers();
	void sendStateToPeers();
	void gameStart();
	void gameStep();
	void executePeerCommands();

public:
	Acceptor(const std::string& config_filepath, LoginQueue& login_queue);
	void run() override;
	void stop();
	~Acceptor() override;
};

#endif
