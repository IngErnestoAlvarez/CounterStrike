#ifndef PEER_H
#define PEER_H

#include "command.h"
#include "my_thread.h"
#include "socket.h"

class Protocolo;
class CommandQueue;

class Peer : public Thread {
private:
	int id;
	bool is_running;
	socket_t socket;
	Protocolo& protocol;
	CommandQueue& command_queue;

public:
	Peer(int id,
		 socket_t& socket,
		 Protocolo& protocol,
		 CommandQueue& command_queue);
	~Peer();
	int getPeerID() const;
	void run() override;
	void sendState();
	void stop();
	bool isRunning();
};

#endif
