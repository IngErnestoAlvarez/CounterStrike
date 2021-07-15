#include "state_queue.h"

StateQueue::StateQueue()
	: queue(), monitor(&queue) {}

bool StateQueue::pop(GameState& state) {
	return this->monitor.pop(state);
}

void StateQueue::push(GameState& state) {
	this->monitor.push(state);
}

void StateQueue::kill() {
	this->monitor.kill();
}
