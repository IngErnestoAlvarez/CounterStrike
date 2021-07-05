#include "queue_monitor.h"

#include <condition_variable>
#include <string>
#include <utility>

typedef std::unique_lock<std::mutex> guard;

template <typename T>
QueueMonitor<T>::QueueMonitor(std::queue<T> *q) : m(), cv(), done(false) {
    this->q = q;
}

template <typename T>
QueueMonitor<T>::QueueMonitor(QueueMonitor const &other) : m() {
    this->q = other.q;
}

template <typename T>
bool QueueMonitor<T>::pop(T &result) {
    if (this->done.load()) return false;
    guard lock(this->m);
    while (this->q->empty()) {
        this->cv.wait(lock);
        if (this->done.load()) return false;
    }
    result = std::move(this->q->front());
    this->q->pop();
    return true;
}

template <typename T>
void QueueMonitor<T>::push(T &element) {
    guard lock(this->m);
    this->q->push(element);
    lock.unlock();
    this->cv.notify_all();
}

template <typename T>
void QueueMonitor<T>::kill() {
    this->done = true;
    this->cv.notify_all();
}
