#ifndef SENDER_H
#define SENDER_H

#include "my_thread.h"
#include <atomic>

class socket_t;
class Protocolo;
class StateQueue;

class Sender : public Thread {
private:
	std::atomic<bool> is_running;
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
};

#endif
