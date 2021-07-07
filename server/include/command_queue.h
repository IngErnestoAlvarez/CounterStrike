#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <mutex>
#include <queue>
#include "command.h"

class CommandQueue {
private:
	std::mutex mutex;
	std::queue<Command> queue;

public:
	CommandQueue();
	~CommandQueue();

	void push(Command command);
	Command pop();
};

#endif
