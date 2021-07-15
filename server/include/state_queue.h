#ifndef STATE_QUEUE_H
#define STATE_QUEUE_H

#include <queue>
#include "game_state.h"
#include "queue_monitor.h"

class StateQueue {
private:
	std::queue<GameState> queue;
	QueueMonitor<GameState> monitor;

public:
	StateQueue();
	bool pop(GameState& state);
	void push(GameState& state);
	void kill();
};

#endif
