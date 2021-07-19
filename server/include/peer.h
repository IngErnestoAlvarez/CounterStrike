#ifndef PEER_H
#define PEER_H

#include "command.h"
#include "command_queue.h"
#include "sender.h"
#include "receiver.h"
#include "state_queue.h"
#include "my_thread.h"
#include "socket.h"

class Protocolo;

class Peer {
private:
	int id;
	socket_t socket;
	Protocolo& protocol;
	CommandQueue& command_queue;
	StateQueue state_queue;
	Sender sender;
	Receiver receiver;

public:
	Peer(int id,
		 socket_t& skt,
		 Protocolo& protocol,
		 CommandQueue& command_queue);
	~Peer();

	int getPeerID() const;
	void start();
	void pushGameState(Game& game);
};

#endif
