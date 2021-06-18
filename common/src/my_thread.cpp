#include "my_thread.h"

#include <iostream>
#include <utility>

Thread::Thread() {}

Thread::~Thread() {}

Thread::Thread(Thread &&other) { this->thread = std::move(other.thread); }

void Thread::start() { this->thread = std::thread(&Thread::run, this); }

void Thread::join() { this->thread.join(); }

Thread &Thread::operator=(Thread &&other) {
    this->thread = std::move(other.thread);
    return *this;
}
