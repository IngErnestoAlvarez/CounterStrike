#ifndef SENDER_H
#define SENDER_H

#include "my_thread.h"

class socket_t;
class Protocolo;
class StateQueue;

class Sender : public Thread {
private:
	bool is_running;
	socket_t& socket;
	Protocolo& protocol;
	StateQueue& state_queue;

public:
	Sender(
      socket_t &socket,
      Protocolo &protocol,
      StateQueue& state_queue);
	~Sender();
	void run() override;
	void stop();
	void sendFinal();
};

#endif
