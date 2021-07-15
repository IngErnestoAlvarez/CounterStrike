#ifndef RECEIVER_H
#define RECEIVER_H

class socket_t;
class Protocolo;
class CommandQueue;

class Receiver : public Thread {
private:
	int id;
	bool is_running;
	socket_t& socket;
	Protocolo& protocol;
	CommandQueue& command_queue;

public:
	Receiver(int id,
			 socket_t& socket,
			 Protocolo& protocol,
			 CommandQueue& command_queue);
	~Receiver();
	void run() override;
};

#endif
