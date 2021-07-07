#ifndef PEER_H
#define PEER_H

#include "my_thread.h"
#include "socket.h"
#include "command.h"
#include "queue_monitor.h"

class Protocolo;

class Peer : public Thread {
private:
	int id;
	socket_t socket;
	Protocolo& protocol;
	QueueMonitor<Command>& command_queue;
	bool is_running;

public:
	Peer(int id,
		 socket_t& socket,
		 Protocolo& protocol,
		 QueueMonitor<Command>& command_queue);
	~Peer();
	int getPeerID() const;
	void run() override;
	void sendState();
	void stop();
};

#endif
