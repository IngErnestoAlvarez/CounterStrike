#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <string>
#include <vector>
#include <queue>

#include "command.h"
#include "my_thread.h"
#include "queue_monitor.h"
#include "socket.h"
#include "protocolo.h"
#include "game_logic/game.h"
#include "command_queue.h"

class Peer;

class Acceptor : public Thread {
private:
	socket_t socket;
	Game game;
	Protocolo protocol;
	std::vector<Peer*> peers;
	std::queue<Command> command_queue;
	QueueMonitor<Command> command_queue_monitor;
	CommandQueue cmd_queue;
	bool is_running;
	void accept();

public:
	Acceptor(const std::string& config_filepath);
	void run() override;
	void stop();
	~Acceptor() override;
};

#endif
