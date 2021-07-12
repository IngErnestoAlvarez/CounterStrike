#include "command_queue.h"

#include "protocolo.h"

CommandQueue::CommandQueue() {}

CommandQueue::~CommandQueue() {}

void CommandQueue::push(Command command) {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->queue.push(command);
}

Command CommandQueue::pop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->queue.empty()) return Command(NO_COMMAND, 0);
    Command command = this->queue.front();
    this->queue.pop();
    return command;
}

bool CommandQueue::isEmpty() {
    std::lock_guard<std::mutex> guard(this->mutex);
    return this->queue.empty();
}
